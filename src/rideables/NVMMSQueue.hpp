#ifndef NVM_MS_QUEUE
#define NVM_MS_QUEUE

#include <atomic>
#include <iostream>
#include "RQueue.hpp"
#include "PersistFunc.hpp"
#include "RCUTracker.hpp"
#include <array>

/* for string */
class NVMMSQueue : public RQueue<std::string>{
private:
    using T = std::array<char,TESTS_VAL_SIZE>;
    struct Node{
        T value;
        atomic_pptr<Node> next;
        std::atomic<int> deqTid;
        
        Node(): next(nullptr), deqTid(-1){};
        Node(std::string val): next(nullptr), deqTid(-1){
            std::copy(val.begin(), val.end(), value.data());
        };
        ~Node(){}
        void* operator new(size_t size){
            // cout<<"persistent allocator called."<<endl;
            // void* ret = malloc(size);
            void* ret = RP_malloc(size);
            if (!ret){
            cerr << "Persistent::new failed: no free memory" << endl;
            exit(1);
            }
            return ret;
        }

        void operator delete(void * p) { 
            RP_free(p); 
        } 
    };

    atomic_pptr<Node>* head;
    atomic_pptr<Node>* tail;
    pptr<T>* returnedVal;
    RCUTracker tracker;

public:
    NVMMSQueue(int task_num): tracker(task_num, 100, 1000, true){
        Persistent::init();
        head = (atomic_pptr<Node>*)RP_malloc(sizeof(atomic_pptr<Node>));
        new (head) atomic_pptr<Node>();
        tail = (atomic_pptr<Node>*)RP_malloc(sizeof(atomic_pptr<Node>));
        new (tail) atomic_pptr<Node>();
        returnedVal = (pptr<T>*)RP_malloc(sizeof(pptr<T>)*task_num);
        new (returnedVal) pptr<T>();
        Node* node = new Node();
        head->store(node);
        tail->store(node);
        for(int i = 0; i < task_num; ++i){
            returnedVal[i] = (T*)RP_malloc(sizeof(T));
            // new (returnedVal[i]) T("");
        }
    }

    ~NVMMSQueue(){
        Persistent::finalize();
    };

    void init_thread(GlobalTestConfig* gtc, LocalTestConfig* ltc){
        Persistent::init_thread(gtc, ltc);
    }

    void enqueue(std::string value, int tid);
    optional<std::string> dequeue(int tid);
};

class NVMMSQueueFactory : public RideableFactory{
    Rideable* build(GlobalTestConfig* gtc){
        return new NVMMSQueue(gtc->task_num);
    }
};

void NVMMSQueue::enqueue(std::string val, int tid){
    Node* node = new Node(val);
    tracker.start_op(tid);
    while(1){
        Node* last = tail->load();
        Node* next = last->next.load();
        if(last == tail->load()){
            if(next == nullptr){
                if((last->next).compare_exchange_strong(next, node)){
                    tail->compare_exchange_strong(last, node);
                    break;
                }
            } else{
                tail->compare_exchange_strong(last, next);
            }
        }
    }
    tracker.end_op(tid);
}

optional<std::string> NVMMSQueue::dequeue(int tid){
    optional<std::string> res = {};
    returnedVal[tid]->fill('\0');
    tracker.start_op(tid);
    while(1){
        Node* first = head->load();
        Node* last = tail->load();
        Node* next = first->next.load();
        if(first == head->load()){
            if(first == last){
                if(next == nullptr){
                    returnedVal[tid]->fill('\0');
                    res.reset();
                    break;
                }
                tail->compare_exchange_strong(last, next);
            } else{
                std::string value = std::string(std::begin(next->value), std::end(next->value));
                int i = -1;
                if(next->deqTid.compare_exchange_strong(i, tid)){
                    std::copy(value.begin(), value.end(), returnedVal[tid]->data());
                    Node* to_retire = first;// failed CAS will write new head into first
                    head->compare_exchange_strong(first, next);
                    
                    res = value;
                    tracker.retire(to_retire, tid);
                    break;
                } else{
                    auto addr = returnedVal[next->deqTid.load()];
                    if(head->load() == first){
                        std::copy(value.begin(), value.end(), addr->data());
                        head->compare_exchange_strong(first, next);
                        
                        res.reset();
                    }
                }
            }
        }
    }
    tracker.end_op(tid);
    return res;
}

#endif