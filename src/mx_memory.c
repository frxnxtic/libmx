#include "../inc/libmx.h"

void *mx_memset(void *b, int c, size_t len) {
    unsigned char *p = b;
    while (len--) {
        *p++ = (unsigned char)c;
    }
    return b;
}

void *mx_memcpy(void *restrict dst, const void *restrict src, size_t n) {
    if (dst == NULL || src == NULL) {
        return NULL;
    }

    unsigned char *d = dst;
    const unsigned char *s = src;
    for (size_t i = 0; i < n; i++) {
        d[i] = s[i];
    }
    return dst;
}

void *mx_memccpy(void *restrict dst, const void *restrict src, int c, size_t n) {
    if (dst == NULL || src == NULL) {
        return NULL;
    }
    unsigned char *d = dst;
    const unsigned char *s = src;
    for (size_t i = 0; i < n; i++) {
        d[i] = s[i];
        if (s[i] == (unsigned char)c) {
            return &d[i + 1];
        }
    }
    return NULL;
}
int mx_memcmp(const void *s1, const void *s2, size_t n) {
    const unsigned char *p1 = s1;
    const unsigned char *p2 = s2;
    for (size_t i = 0; i < n; i++) {
        if (p1[i] != p2[i]) {
            return p1[i] - p2[i];
        }
    }
    return 0;
}
void *mx_memchr(const void *s, int c, size_t n) {
    const unsigned char *p = s;
    for (size_t i = 0; i < n; i++) {
        if (p[i] == (unsigned char)c) {
            return (void *)&p[i];
        }
    }
    return NULL;
}
void *mx_memrchr(const void *s, int c, size_t n) {
    const unsigned char *p = s;
    for (size_t i = n; i > 0; i--) {
        if (p[i] == (unsigned char)c) {
            return (void *)&p[i];
        }
    }
    return NULL;
}
void *mx_memmem(const void *big, size_t big_len, const void *little, 
                size_t little_len) {
    const unsigned char *b = big;
    const unsigned char *l = little;
    for (size_t i = 0; i < big_len; i++) {
        if (b[i] == l[0]) {
            if (mx_memcmp(&b[i], l, little_len) == 0) {
                return (void *)&b[i];
            }
        }
    }
    return NULL;
}
void *mx_memmove(void *dst, const void *src, size_t len) {
    unsigned char *d = dst;
    const unsigned char *s = src;
    unsigned char *temp = (unsigned char *)malloc(len);
    if (temp == NULL) {
        return NULL;
    }
    for (size_t i = 0; i < len; i++) {
        temp[i] = s[i];
    }
    for (size_t i = 0; i < len; i++) {
        d[i] = temp[i];
    }
    free(temp);
    return dst;
}
void *mx_realloc(void *ptr, size_t size) {
    if (ptr == NULL) {
        return malloc(size);
    }
    if (size == 0) {
        free(ptr);
        return NULL;
    }
    void *new_ptr = malloc(size);
    if (new_ptr == NULL) {
        return NULL;
    }
    mx_memcpy(new_ptr, ptr, size);
    free(ptr);
    return new_ptr; 
}
