#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <ulib/search_line.h>
#include <unistd.h>

int comp_line(const char *line, void *param) {
    return strcmp(line, (const char *)param);
}

int main() {
    int fd = open("./search_line.data", O_RDONLY);

    assert(fd != -1);
    assert(findfirstline(fd, comp_line, (void *)"world", 1024) == 18);
    // can't find
    assert(findfirstline(fd, comp_line, (void *)"world hello", 1024) == -1);

    close(fd);

    printf("passed\n");

    return 0;
}
