/* mx_string.c */

#include "../inc/libmx.h"

/**
    * mx_strlen - Computes the length of a string
    * @s: The string to measure
*/
int mx_strlen(const char *s) {
    if (s == NULL) {
        return -2;
    }

    const char *p = s;
    while (*p) p++;
    return p - s;
}

