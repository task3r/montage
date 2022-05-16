#include "ralloc.hpp"

#include <pthread.h>

#include <atomic>
#include <cstdio>
#include <iostream>
// #include "thread_util.hpp"

using namespace std;

const int THREAD_NUM = 4;
// ralloc* alloc;
atomic<bool> start{false};

void *malloc_free_loop(void *args) {
    while (!start.load())
        ;
    int iters = *((int *)args);
    int **p = (int **)RP_malloc(iters * sizeof(int *));
    int ret = 1;
    for (int i = 0; i < iters; i++) {
        p[i] = (int *)RP_malloc(sizeof(int));
        *p[i] = i;
        ret = *p[i] + 1;
        if (i % 1000000 == 0) fprintf(stderr, "%p: %d\n", p[i], *p[i]);
    }
    for (int i = 0; i < iters; i++) {
        RP_free(p[i]);
    }
    printf("final: %d\n", ret);
    RP_free(p);
    return nullptr;
}
static void test_unhooked(int iters) {
    // timedelta_t timer;
    // timer_start(&timer);
    pthread_t thread_id[THREAD_NUM];
    for (int i = 0; i < THREAD_NUM; i++)
        pthread_create(&thread_id[i], NULL, malloc_free_loop, (void *)&iters);
    start.store(true);
    for (int i = 0; i < THREAD_NUM; i++) pthread_join(thread_id[i], NULL);
}
int main() {
    int iters = 10 * 1000 * 1000;
    printf("Benchmarking hooks with %d iterations:\n", iters);
    if (RP_init("test") == 1) {
        int cnt = 0;
        cout << "Restart. Calling Ralloc recovery routine..." << endl;
        auto iter = RP_recover();
        if (iter.is_dirty()) {
            cout << "Dirty restart" << endl;
            while (!iter.is_last()) {
                cnt++;
                ++iter;
            }
        } else {
            cout << "Clean restart" << endl;
            while (!iter.is_last()) {
                cnt++;
                ++iter;
            }
        }
        RP_recover();
        cout << "Iterator went through: " << cnt << endl;
        cout << "Ralloc recovery done!" << endl;
    }
    test_unhooked(iters);

    // RP_close();
    RP_simulate_crash();

    if (RP_init("test") == 1) {
        int cnt = 0;
        cout << "Restart. Calling Ralloc recovery routine..." << endl;
        {
            auto iter = RP_recover();
            if (iter.is_dirty()) {
                cout << "Dirty restart" << endl;
                while (!iter.is_last()) {
                    cnt++;
                    ++iter;
                }
            } else {
                cout << "Clean restart" << endl;
                while (!iter.is_last()) {
                    cnt++;
                    ++iter;
                }
            }
        }
        auto iter = RP_recover();
        if (iter.is_dirty()) {
            cout << "Dirty restart" << endl;
            while (!iter.is_last()) {
                cnt++;
                ++iter;
            }
        } else {
            cout << "Clean restart" << endl;
            while (!iter.is_last()) {
                cnt++;
                ++iter;
            }
        }
        cout << "Iterator went through: " << cnt << endl;
        cout << "Ralloc recovery done!" << endl;
    }
    RP_close();
    cout << "done!\n";
    return 0;
}
