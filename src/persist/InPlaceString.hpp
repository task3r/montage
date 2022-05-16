#ifndef INPLACESTRING_HPP
#define INPLACESTRING_HPP

#include <cstring>
#include <string>

#include "EpochSys.hpp"
#include "pptr.hpp"

namespace pds {

// extern __thread int pds::_tid;

// class InPlaceString : public PBlk{
//     pptr<PBlkArray<char>> char_array;

// public:
//     // TODO: it's kind of cheating to use epochs[] here...
//     InPlaceString(PBlk* owner, const std::string& str) : PBlk(owner),
//         char_array(esys->alloc_pblk_array<char>(owner, str.size()+1,
//         epochs[EpochSys::tid].ui)) { memcpy(char_array->content, str.c_str(),
//         str.size()+1); esys->register_update_pblk(char_array,
//         epochs[EpochSys::tid].ui);
//     }
//     InPlaceString(const InPlaceString& oth): PBlk(oth),
//         char_array(esys->copy_pblk_array<char>(oth.char_array,
//         epochs[EpochSys::tid].ui)) {}

//     pptr<PBlk> get_data(){
//         return pptr<PBlk>(char_array);
//     }

//     virtual ~InPlaceString(){
//         // It's safe to reclaim char_array directly since the owner must deep
//         copy itself ahead, including InPlaceString and char_array
//         PDELETE_DATA((PBlkArray<char>*)char_array);
//     }

//     InPlaceString& operator = (const InPlaceString &oth){ //assignment
//         // if(char_array!=nullptr) // char_array being null is impossible
//         PDELETE_DATA((PBlkArray<char>*)char_array);
//         char_array = esys->copy_pblk_array<char>(oth.char_array,
//         epochs[EpochSys::tid].ui); return *this;
//     }

//     InPlaceString& operator=(const std::string& str){
//         PDELETE_DATA((PBlkArray<char>*)char_array);
//         char_array = esys->alloc_pblk_array<char>(this, str.size()+1,
//         epochs[EpochSys::tid].ui); memcpy(char_array->content, str.c_str(),
//         str.size()+1); esys->register_update_pblk(char_array,
//         epochs[EpochSys::tid].ui); return *this;
//     }

//     std::string std_str()const{
//         // size-1 since the last char is NULL
//         return std::string((char*)char_array->content,
//         char_array->get_size()-1);
//     }

//     operator std::string() const {
//         return std_str();
//     }

// };

template <size_t cap = 1025>
class InPlaceString {
    size_t size_;
    char char_array[cap + 1];

   public:
    InPlaceString(PBlk* owner, const std::string& str) : size_(str.size()) {
        assert(size_ <= cap);
        memcpy(char_array, str.c_str(), str.size() + 1);
        assert(char_array[size_] == '\0');
    }
    InPlaceString(const InPlaceString<cap>& oth) {
        size_ = oth.size();
        assert(size_ <= cap);
        memcpy(char_array, oth.char_array, size_ + 1);
        assert(char_array[size_] == '\0');
    }
    InPlaceString(const std::string& str) : size_(str.size()) {
        assert(size_ <= cap);
        memcpy(char_array, str.c_str(), str.size() + 1);
        assert(char_array[size_] == '\0');
    }
    InPlaceString() : size_(0) { char_array[0] = '\0'; }
    InPlaceString<cap>& operator=(const InPlaceString<cap>& oth) {  // assignment
        size_ = oth.size();
        assert(size_ <= cap);
        memcpy(char_array, oth.char_array, size_ + 1);
        assert(char_array[size_] == '\0');
        return *this;
    }

    InPlaceString<cap>& operator=(const std::string& str) {
        size_ = str.size();
        assert(size_ <= cap);
        memcpy(char_array, str.c_str(), size_ + 1);
        assert(char_array[size_] == '\0');
        return *this;
    }
    int compare(const std::string& s) {
        assert(c_str()[size()] == '\0');
        return strcmp(c_str(), s.c_str());
    }
    friend bool operator==(const std::string& a, const InPlaceString<cap>& b) {
        assert(b.c_str()[b.size()] == '\0');
        if (a.size() != b.size()) {
            return false;
        }
        return (strcmp(a.c_str(), b.c_str()) == 0);
    }
    friend bool operator==(const InPlaceString<cap>& a, const std::string& b) {
        return (b == a);
    }
    friend bool operator!=(const std::string& a, const InPlaceString<cap>& b) {
        return !(a == b);
    }
    friend bool operator!=(const InPlaceString<cap>& a, const std::string& b) {
        return !(b == a);
    }
    friend bool operator<(const std::string& a, const InPlaceString<cap>& b) {
        assert(b.c_str()[b.size()] == '\0');
        return (strcmp(a.c_str(), b.c_str()) < 0);
    }
    friend bool operator<(const InPlaceString<cap>& a, const std::string& b) {
        assert(a.c_str()[a.size()] == '\0');
        return (strcmp(a.c_str(), b.c_str()) < 0);
    }
    friend bool operator>(const std::string& a, const InPlaceString<cap>& b) {
        return (b < a);
    }
    friend bool operator>(const InPlaceString<cap>& a, const std::string& b) {
        return (b < a);
    }
    friend bool operator<=(const std::string& a, const InPlaceString<cap>& b) {
        return !(a > b);
    }
    friend bool operator<=(const InPlaceString<cap>& a, const std::string& b) {
        return !(a > b);
    }
    friend bool operator>=(const std::string& a, const InPlaceString<cap>& b) {
        return !(a < b);
    }
    friend bool operator>=(const InPlaceString<cap>& a, const std::string& b) {
        return !(a < b);
    }

    std::string std_str() const {
        // size-1 since the last char is NULL
        return std::string(char_array, size_);
    }

    operator std::string() const { return std_str(); }

    const char* c_str() const {
        assert(char_array[size_] == '\0');
        return char_array;
    }

    size_t size() const { return size_; }
};

#include <functional>

#include "PersistFunc.hpp"
template <size_t cap = 1025>
class TrivialInPlaceString {
    char content[cap];
    size_t sz;

   public:
    inline size_t size() const { return sz; }
    TrivialInPlaceString(const std::string& str) {
        sz = str.size();
        assert(str.size() <= cap);
        memcpy((char*)content, str.data(), str.size());
    }

    ~TrivialInPlaceString() {}
#ifndef MNEMOSYNE
    std::string_view std_str() const {
        // size-1 since the last char is NULL
        return std::string_view((char*)content, sz);
    }
#else
    std::string std_str() const {
        // size-1 since the last char is NULL
        return std::string((char*)content, sz);
    }
#endif
    void flush() const {
        if (content != nullptr)
            persist_func::clwb_range_nofence((char*)content, sz);
    }

    operator std::string() const {
        // size-1 since the last char is NULL
        return std::string((char*)content, sz);
    }

    bool operator==(const TrivialInPlaceString<cap>& other) const {
        return std_str() == other.std_str();
    }
    TrivialInPlaceString<cap>& operator=(const std::string& str) {
        if (str.size() <= cap) {
            memcpy((char*)content, str.data(), str.size());
            sz = str.size();
        } else {
            printf("String length exceeds TrivialInPlaceString capacity!\n");
            exit(1);
        }
        return *this;
    }
    int compare(const std::string& str) const {
        int ret = strncmp((char*)content, str.data(), min(sz, str.size()));
        if (ret == 0) {
            if (sz == str.size())
                return 0;
            else if (sz < str.size())
                return -1;
            else
                return 1;
        } else {
            return ret;
        }
    }
};

}  // namespace pds

namespace std {
template <size_t cap>
struct hash<pds::TrivialInPlaceString<cap>> {
#ifndef MNEMOSYNE
    static hash<string_view> str_hash;
#else
    static hash<string> str_hash;
#endif
    size_t operator()(const pds::TrivialInPlaceString<cap>& x) const {
        return str_hash(x.std_str());
    }
};
}  // namespace std

#endif
