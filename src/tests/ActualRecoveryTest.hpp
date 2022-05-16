#ifndef ACTUALRECOVERYTEST
#define ACTUALRECOVERYTEST

/*
 * This is a test to test recovery after actual crash (not simulated)
 */

#include <unordered_map>

#include "AllocatorMacro.hpp"
#include "Persistent.hpp"
#include "Recoverable.hpp"
#include "TestConfig.hpp"

template <class K, class V>
class ActualRecoveryTest : public Test {
   public:
    RMap<K, V>* m;
    Recoverable* rec;
    size_t ins_cnt = 1000000;
    size_t range = ins_cnt * 10;
    size_t key_size = TESTS_KEY_SIZE;
    size_t val_size = TESTS_VAL_SIZE;
    pthread_barrier_t sync_point;
    ActualRecoveryTest() {}
    void init(GlobalTestConfig* gtc);
    void parInit(GlobalTestConfig* gtc, LocalTestConfig* ltc);
    int execute(GlobalTestConfig* gtc, LocalTestConfig* ltc);
    void cleanup(GlobalTestConfig* gtc);

    inline K fromInt(uint64_t v);
};

template <class K, class V>
void ActualRecoveryTest<K, V>::parInit(GlobalTestConfig* gtc,
                                       LocalTestConfig* ltc) {
    m->init_thread(gtc, ltc);
}

template <class K, class V>
void ActualRecoveryTest<K, V>::init(GlobalTestConfig* gtc) {
    Rideable* ptr = gtc->allocRideable();
    m = dynamic_cast<RMap<K, V>*>(ptr);
    if (!m) {
        errexit("ActualRecoveryTest must be run on RMap<K,V> type object.");
    }
    rec = dynamic_cast<Recoverable*>(ptr);
    if (!rec) {
        errexit("ActualRecoveryTest must be run on Recoverable type object.");
    }
    if (gtc->checkEnv("InsCnt")) {
        ins_cnt = stoll(gtc->getEnv("InsCnt"));
        range = ins_cnt * 10;
    }

    /* set interval to inf so this won't be killed by timeout */
    gtc->interval = numeric_limits<double>::max();
    pthread_barrier_init(&sync_point, NULL, gtc->task_num);
}

template <class K, class V>
inline K ActualRecoveryTest<K, V>::fromInt(uint64_t v) {
    return (K)v;
}

template <>
inline std::string ActualRecoveryTest<std::string, std::string>::fromInt(
    uint64_t v) {
    auto _key = std::to_string(v);
    return "user" + std::string(key_size - _key.size() - 4, '0') + _key;
}

template <class K, class V>
int ActualRecoveryTest<K, V>::execute(GlobalTestConfig* gtc,
                                      LocalTestConfig* ltc) {
    return rec->recover(false);
}

template <class K, class V>
void ActualRecoveryTest<K, V>::cleanup(GlobalTestConfig* gtc) {
    delete m;
}

#endif
