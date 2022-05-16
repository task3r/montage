#include <assert.h>

#include <BaseMeta.hpp>
#include <rpmalloc.hpp>

int main() {
    pm_init();
    unsigned *al = pm_get_root<unsigned>(0);
    //  pm_recover();
    for (int i = 0; i < 1000; ++i) {
        assert(al[i] == 0xDEADBEEF);
    }
}
