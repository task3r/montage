#ifndef SMALLMAPTEST_HPP
#define SMALLMAPTEST_HPP

/*
 * This is a test with fixed number of operations for mappings.
 */

#include <iostream>

#include "RMap.hpp"
#include "TestConfig.hpp"

using std::string;

class SmallMapTest : public Test {
   public:
    RMap<string, string>* m;
    uint64_t total_ops;
    SmallMapTest(int op = 1000000) { total_ops = op; }

    void parInit(GlobalTestConfig* gtc, LocalTestConfig* ltc) {
        m->init_thread(gtc, ltc);
    }

    void init(GlobalTestConfig* gtc) {
        Rideable* ptr = gtc->allocRideable();
        m = dynamic_cast<RMap<string, string>*>(ptr);
        if (!m) {
            errexit("SmallMapTest must be run on RMap<K,V> type object.");
        }
        if (gtc->checkEnv("N")) {
            total_ops = stoll(gtc->getEnv("N"));
        }
        printf("SmallMapTest with %ld ops\n", total_ops);
    }

    int execute(GlobalTestConfig* gtc, LocalTestConfig* ltc) {
        int tid = ltc->tid;
        for (size_t i = 1; i <= total_ops; i++) {
            string key = this->fromInt(i);
            m->insert(key, key, tid);
        }

        for (size_t i = total_ops; i > 0; i--) {
            string key = this->fromInt(i);
            string value = this->fromInt(i * 2);
            m->put(key, value, tid);
        }

        for (size_t i = 1; i <= total_ops; i++) {
            string key = this->fromInt(i);
            m->remove(key, tid);
        }

        return total_ops;
    }

    void cleanup(GlobalTestConfig* gtc) { delete m; }

    inline string fromInt(uint64_t v) { return std::to_string(v); }
};

#endif
