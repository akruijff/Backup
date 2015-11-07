
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

#include "backup-util.h"

int setBackupStamp(char *dst, size_t size, const char *base, const char *hostname, const struct tm *tm) {
    if (dst == NULL)
        return 1;
    if (base == NULL)
        return 2;
    if (size < strlen(base) + 22)
        return 3;
    if (hostname == NULL)
        return 4;
    if (tm == NULL)
        return 5;
    sprintf(dst, "%s/%s_%04i-%02i-%02i_%02i-%02i-%02i", base, hostname, 
            1900 + tm->tm_year, tm->tm_mon, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
    return 0;
}

struct tm *getCurrentTime(bool local) {
    time_t clock;
    time(&clock);
    return local ? localtime(&clock) : gmtime(&clock);
}

size_t copyPrefix(char *dst, size_t size, const char *prefix);
size_t copyHostname(char *dst, size_t size);
size_t copyPostfix(char *dst, size_t size, const char *postfix);

int getConfigFile(char *dst, size_t size, const char *prefix, const char *postfix) {
    if (dst == NULL)
        return size != 0 ? 1 : 0;

    size_t tmp = copyPrefix(dst, size, prefix);
    if (prefix != NULL && tmp == 0 && *prefix != 0)
        return 2;
    size -= tmp, dst += tmp;

    *dst = '.';
    if (size < 1)
        return 3;
    --size, ++dst;

    tmp = copyHostname(dst, size);
    if (tmp == 0)
        return 4;
    size -= tmp, dst += tmp;

    tmp = copyPostfix(dst, size, postfix);
    if (postfix != NULL && tmp == 0)
        return 5;
    return 0;
}

size_t copyPrefix(char *dst, size_t size, const char *prefix) {
    if (prefix == NULL)
        return 0;
    size_t n = strlen(prefix);
    if (size < n + 1)
        return 0;
    memcpy(dst, prefix, n);
    return n;
}

size_t copyHostname(char *dst, size_t size) {
    return gethostname(dst, size) != 0 ? 0 : strlen(dst);
}

size_t copyPostfix(char *dst, size_t size, const char *postfix) {
    if (postfix == NULL)
        return 0;
    size_t n = strlen(postfix);
    if (size < n + 1)
        return 0;
    strcpy(dst, postfix);
    return n;
}
