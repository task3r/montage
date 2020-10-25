/*
 * API for nonblocking data structures which provide:
 *  atomic_dword_t: Atomic double word for storing pointers that point
 *                  to nodes, which link payloads in.
 */

#ifndef LLSC_HPP
#define LLSC_HPP
#include <atomic>

#include <cassert>
// #include <immintrin.h>

#include "ConcurrentPrimitives.hpp"
#include "EpochSys.hpp"
namespace pds{

struct sc_desc_t;
struct dword_t{
    uint64_t val;
    uint64_t cnt;
    inline bool is_desc() const {
        return (cnt & 3UL) == 1UL;
    }
    inline sc_desc_t* get_desc() const {
        assert(is_desc());
        return reinterpret_cast<sc_desc_t*>(val);
    }
    template <typename T>
    inline T get_val() const {
        static_assert(sizeof(T) == sizeof(uint64_t), "sizes do not match");
        return reinterpret_cast<T>(val);
    }
    dword_t(uint64_t v, uint64_t c) : val(v), cnt(c) {};
    dword_t() : dword_t(0, 0) {};
}__attribute__((aligned(16)));

extern thread_local uint64_t local_cnt;
extern padded<sc_desc_t>* local_descs;
extern EpochSys* esys;
extern padded<uint64_t>* epochs;

template <typename T = uint64_t>
class atomic_dword_t{
    static_assert(sizeof(T) == sizeof(uint64_t), "sizes do not match");
public:
    // for cnt in dword:
    // desc: ....01
    // real val: ....00
    std::atomic<dword_t> dword;
    T load();
    T load_linked();
    bool store_conditional(T expected, const T& desired);
    void store(const T& desired);
    // Wentao: count has to start from 4, since 0 is reserved for
    // noting local_cnt isn't assigned by a valid number
    atomic_dword_t(const T& v) : dword(dword_t(reinterpret_cast<uint64_t>(v), 4)){};
    atomic_dword_t() : atomic_dword_t(T()){};
};

struct sc_desc_t{
private:
    // for cnt in dword:
    // in progress: ....01
    // committed: ....10 TODO
    // aborted: ....11
    std::atomic<dword_t> dword;
    const uint64_t old_val;
    const uint64_t new_val;
    const uint64_t cas_epoch;
    inline void abort(dword_t _d){
        // bring cnt from ..01 to ..11
        dword_t expected (_d.val, (_d.cnt & ~0x3UL) | 1UL); // in progress
        dword_t desired = expected;
        desired.cnt += 2;
        dword.compare_exchange_strong(expected, desired);
    }
    inline void commit(dword_t _d){
        // bring cnt from ..01 to ..10
        dword_t expected (_d.val, (_d.cnt & ~0x3UL) | 1UL); // in progress
        dword_t desired(expected);
        desired.cnt += 1;
        dword.compare_exchange_strong(expected, desired);
    }
    inline bool committed(dword_t _d) const {
        return (_d.cnt & 0x3UL) == 2UL;
    }
    inline bool in_progress(dword_t _d) const {
        return (_d.cnt & 0x3UL) == 1UL;
    }
    inline bool match(dword_t old_d, dword_t new_d) const {
        return ((old_d.cnt & ~0x3UL) == (new_d.cnt & ~0x3UL)) && 
               (old_d.val == new_d.val);
    }
    void cleanup(dword_t old_d){
        // must be called after desc is aborted or committed
        dword_t new_d = dword.load();
        if(!match(old_d,new_d)) return;
        assert(!in_progress(new_d));
        dword_t expected(reinterpret_cast<uint64_t>(this),(new_d.cnt & ~0x3UL) | 1UL);
        if(committed(new_d)) {
            // bring cnt from ..10 to ..00
            reinterpret_cast<atomic_dword_t<>*>(
                new_d.val)->dword.compare_exchange_strong(
                expected, 
                dword_t(new_val,new_d.cnt + 2));
        } else {
            //aborted
            // bring cnt from ..11 to ..00
            reinterpret_cast<atomic_dword_t<>*>(
                new_d.val)->dword.compare_exchange_strong(
                expected, 
                dword_t(old_val,new_d.cnt + 1));
        }
    }
public:
    inline bool committed() const {
        return committed(dword.load());
    }
    inline bool in_progress() const {
        return in_progress(dword.load());
    }
    inline void try_complete(EpochSys* esys, uint64_t addr){
        dword_t _d = dword.load();
        if(_d.val!=addr) return;
        if(in_progress(_d)){
            if(esys->check_epoch(cas_epoch)){
                commit(_d);
            } else {
                abort(_d);
            }
        }
        cleanup(_d);
    }
    sc_desc_t( uint64_t c, uint64_t a, uint64_t o, 
                uint64_t n, uint64_t e) : 
        dword(dword_t(a,c)), old_val(o), new_val(n), cas_epoch(e){};
    sc_desc_t() : sc_desc_t(0,0,0,0,0){};
};

template<typename T>
T atomic_dword_t<T>::load(){
    dword_t r;
    do { 
        r = dword.load();
        if(r.is_desc()) {
            sc_desc_t* D = r.get_desc();
            D->try_complete(esys, reinterpret_cast<uint64_t>(this));
        }
    } while(r.is_desc());
    return r.get_val<T>();
}

template<typename T>
T atomic_dword_t<T>::load_linked(){
    dword_t r;
    do { 
        r = dword.load();
        if(r.is_desc()) {
            sc_desc_t* D = r.get_desc();
            D->try_complete(esys, reinterpret_cast<uint64_t>(this));
        }
    } while(r.is_desc());
    local_cnt = r.cnt;
    return r.get_val<T>();
}

template<typename T>
bool atomic_dword_t<T>::store_conditional(T expected, const T& desired){
    assert(local_cnt != 0); // ll should be called before sc
    // if (_xbegin() == _XBEGIN_STARTED) {
    //     dword_t r = dword.load();
    //     if(!r.is_desc()){
    //         if( r.cnt!=local_cnt ||
    //             r.val!=reinterpret_cast<uint64_t>(expected)){
    //             // local_cnt = 0;
    //             _xabort(1);
    //             return false;
    //         }
    //         if(!esys->check_epoch(epochs[_tid].ui)){
    //             // local_cnt = 0;
    //             _xabort(1);
    //             return false;
    //         }
    //         dword_t new_r (reinterpret_cast<uint64_t>(desired), r.cnt+4);
    //         dword.store(new_r);
    //         local_cnt = 0;
    //         _xend();
    //         return true;
    //     } else {
    //         // we don't handle cases when r is a descriptor
    //         _xabort(1);
    //         return false;
    //     }
    // }
    // txn fails; fall back routine
    dword_t r = dword.load();
    if(r.is_desc()){
        sc_desc_t* D = r.get_desc();
        D->try_complete(esys, reinterpret_cast<uint64_t>(this));
        local_cnt = 0;
        return false;
    } else {
        if( r.cnt!=local_cnt || 
            r.val!=reinterpret_cast<uint64_t>(expected)) {
            local_cnt = 0;
            return false;
        }
    }
    assert(epochs[_tid].ui != NULL_EPOCH);
    new (&local_descs[_tid].ui) sc_desc_t(r.cnt+1, 
                                reinterpret_cast<uint64_t>(this), 
                                reinterpret_cast<uint64_t>(expected), 
                                reinterpret_cast<uint64_t>(desired), 
                                epochs[_tid].ui);
    dword_t new_r(reinterpret_cast<uint64_t>(&local_descs[_tid].ui), r.cnt+1);
    if(!dword.compare_exchange_strong(r,new_r)){
        local_cnt = 0;
        return false;
    }
    local_descs[_tid].ui.try_complete(esys, reinterpret_cast<uint64_t>(this));
    local_cnt = 0;
    if(local_descs[_tid].ui.committed()) return true;
    else return false;
}

template<typename T>
void atomic_dword_t<T>::store(const T& desired){
    // this function must be used only when there's no data race
    dword_t r = dword.load();
    dword_t new_r(reinterpret_cast<uint64_t>(desired),r.cnt+4);
    dword.store(new_r);
}

}
#endif