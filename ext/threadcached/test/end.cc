/* -*- Mode: C; tab-width: 4; c-basic-offset: 4; indent-tabs-mode: nil -*- */
#include <assert.h>
#include <pku_memcached.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <string>

int main() {
    memcached_init(1);
    memcached_end();
    memcached_close();
    return 0;
}
