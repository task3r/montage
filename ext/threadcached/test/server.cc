#include <memcached.h>
#include <pku_memcached.h>

extern bool server_flag;
int main() {
    server_flag = true;
    memcached_init(1);
    memcached_start_server();
}
