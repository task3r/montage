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

static const char* recovery_status_label[] = {"INSERTED", "PUTTED", "EMPTY"};
enum RecoveryStatus { INSERTED, PUTTED, EMPTY };

class ActualRecoveryTest : public Test {
   public:
    Rideable* rideable;
    Recoverable* rec;
    RMap<string, string>* m;
    bool extra_recovery = false;
    uint64_t total_ops = 1000;
    bool should_throw = false;
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
        m = dynamic_cast<RMap<string, string>*>(rideable);
        if (!m) {
            errexit("SmallMapTest must be run on a RMap");
        }
        if (gtc->checkEnv("Verify")) {
            extra_recovery = true;
            if (gtc->checkEnv("N")) {
                total_ops = stoll(gtc->getEnv("N"));
            }
        }
    }

    inline string fromInt(uint64_t v) { return std::to_string(v); }

    void check(bool test, RecoveryStatus current, size_t idx, size_t value,
               const char* message) {
        if (!test) {
            std::cout << "failed assertion: " << message << "\n"
                      << "current status: " << recovery_status_label[current]
                      << ", idx: " << idx << ", value: " << value << std::endl;
            throw 1;
        }
    }

    int execute(GlobalTestConfig* gtc, LocalTestConfig* ltc) {
        if (!extra_recovery) return 1;

        int tid = ltc->tid;
        string last_changed;
        bool crashed;
        RecoveryStatus status = EMPTY;
        for (size_t i = 1; i <= total_ops; i++) {
            string key = fromInt(i);
            optional<string> value = m->get(key, tid);
            if (!value.has_value()) {
                if (status != EMPTY) {
                    check(status == INSERTED, status, i, 0,
                          "status == INSERTED && crashed");
                    if (!crashed) last_changed = key;
                    crashed = true;
                }
            } else {
                size_t actual_value = stoi(value.value());
                switch (status) {
                    case EMPTY:
                        if (actual_value == i * 2) {
                            status = PUTTED;
                            last_changed = key;
                        } else {
                            check(actual_value == i, status, i, 0,
                                  "actual_value == i");
                            check(i == 1, status, i, 0, "i == 1");
                            status = INSERTED;
                            last_changed = key;
                        }
                        break;
                    case INSERTED:
                        if (actual_value == i * 2) {
                            status = PUTTED;
                            last_changed = key;
                        } else {
                            check(actual_value == i, status, i, 0,
                                  "actual_value == i");
                        }
                        break;
                    case PUTTED:
                        check(actual_value == i * 2, status, i, 0,
                              "actual_value == i*2");
                        break;
                }
            }
        }
        std::cout << "recovery status: " << recovery_status_label[status]
                  << ", last changed on: " << last_changed << std::endl;
        return 1;
    }

    void cleanup(GlobalTestConfig* gtc) { delete rideable; }
};

#endif
