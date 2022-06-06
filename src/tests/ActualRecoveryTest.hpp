#ifndef ACTUALRECOVERYTEST
#define ACTUALRECOVERYTEST

/*
 * This is a test to test recovery after actual crash (not simulated)
 */

#include <unordered_map>

#include "MontageHashTable.hpp"
#include "RMap.hpp"
#include "Recoverable.hpp"
#include "TestConfig.hpp"

class ActualRecoveryTest : public Test {
   public:
    Rideable* rideable;
    Recoverable* rec;
    MontageHashTable<string, string>* m;
    bool extra_recovery = false;
    uint64_t total_ops = 1000;
    ActualRecoveryTest() {}

    void parInit(GlobalTestConfig* gtc, LocalTestConfig* ltc) {
        rideable->init_thread(gtc, ltc);
    }

    void init(GlobalTestConfig* gtc) {
        rideable = gtc->allocRideable();
        rec = dynamic_cast<Recoverable*>(rideable);
        if (!rec) {
            errexit(
                "ActualRecoveryTest must be run on Recoverable type object.");
        }
        m = dynamic_cast<MontageHashTable<string, string>*>(rideable);
        if (!m) {
            errexit("SmallMapTest must be run on a MontageHashTable");
        }
        if (gtc->checkEnv("Verify")) {
            extra_recovery = true;
            if (gtc->checkEnv("N")) {
                total_ops = stoll(gtc->getEnv("N"));
            }
        }
    }

    inline string fromInt(uint64_t v) { return std::to_string(v); }

    int execute(GlobalTestConfig* gtc, LocalTestConfig* ltc) {
        m->recover(false);
        if (extra_recovery) {
            int tid = ltc->tid;
            bool stopped = false;
            string stopped_at;
            for (size_t i = 0; i < total_ops; i++) {
                string key = fromInt(i);
                optional<string> value = m->get(key, tid);
                if (!value.has_value()) {
                    if (!stopped) {
                        stopped = true;
                        stopped_at = key;
                    }
                } else if (stopped) {
                    std::cout << "found key:" << key
                              << " after missing from key: " << stopped_at
                              << std::endl;
                    exit(1);
                } else {
                    assert(value.value() == key);
                }
            }
            if (!stopped) {
                std::cout << "recovery complete, found everything" << std::endl;
            } else {
                std::cout << "recovery complete, missed from key: "
                          << stopped_at << " onwards" << std::endl;
            }
        }
        return 1;
    }

    void cleanup(GlobalTestConfig* gtc) {
        // delete rideable;
    }
};

#endif
