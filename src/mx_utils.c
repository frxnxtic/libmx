/* mx_utils.c */

#include "../inc/libmx.h"

/**
    * mx_printchar - Prints a single character to the standart output.
    * @c: The character to print.
*/
void mx_printchar(char c) {
    write(1, &c, 1);
}

/**
    * mx_print_unicode - Prints a Unicode character to the standart output
    * @c: The Unicode character to print.
*/
void mx_print_unicode(wchar_t c) {
    if (c <= 0x7F) {
        mx_printchar(c);
    } else if (c <= 0x7FF) {
        mx_printchar(0xC0 | (c >> 6));
        mx_printchar(0x80 | (c & 0x3F));
    } else if (c <= 0xFFFF) {
        mx_printchar(0xE0 | (c >> 12));
        mx_printchar(0x80 | ((c >> 6) & 0x3F));
        mx_printchar(0x80 | (c & 0x3F));
    } else if (c <= 0x10FFFF) {
        mx_printchar(0xF0 | (c >> 18));
        mx_printchar(0x80 | ((c >> 12) & 0x3F));
        mx_printchar(0x80 | ((c >> 6) & 0x3F));
        mx_printchar(0x80 | (c & 0x3F));
    }
}


/**
    * mx_printstr - Prints the string to the standart output.
    * @s: The string to print.
*/
void mx_printstr(const char *s) {
    if (s == NULL) {
        return;
    }

    int count = 0;

    while (s[count] != '\0') {
        mx_printchar(s[count]);
        count++;
    }
}

void mx_print_strarr(char **arr, const char *delim) {
    if (!arr || !delim) {
        return;
    }

    for (int i = 0; arr[i]; i++) {
        mx_printstr(arr[i]);

        if (arr[i + 1]) {
            mx_printstr(delim);
        }
    }
}

void mx_printint(int n) {
    if (n < 0) {
        mx_printchar('-');
        if (n == INT_MIN) {
            mx_printchar('2');
            n = 147483648;
        } else {
            n = -n;
        }
    }

    if (n >= 10) {
        mx_printint(n / 10);
    }

    mx_printchar((n % 10) + '0');
}

double mx_pow(double n, unsigned int pow) {
    double result = 1;

    for (unsigned int i = 0; i < pow; i++) {
        if (result > INT_MAX / n) {
            return -1;
        }

        result *= n;
    }

    return result;
}

int mx_sqrt(int x) {
    if (x < 0) {
        return 0;
    }

    int result = 0;

    for (int i = 1; i <= x / i; i++) {
        result = i;
    }

    return result;
}

char *mx_nbr_to_hex(unsigned long nbr) {
    if (nbr == 0) {
        char *zero = (char *)malloc(2);
        zero[0] = '0';
        zero[1] = '\0';
        return zero;
    }

    unsigned long temp = nbr;
    int len = 0;

    while (temp > 0) {
        temp /= 16;
        len++;
    }

    char *hex = (char *)malloc(len + 1);
    if (hex == NULL) {
        return NULL;
    }

    hex[len] = '\0';

    while (nbr > 0) {
        unsigned long remain = nbr % 16;
        if (remain < 10) {
            hex[--len] = '0' + remain;
        } else {
            hex[--len] = 'a' + (remain - 10);
        }
        nbr /= 16;
    }

    return hex;
}

unsigned long mx_hex_to_nbr(const char *hex);

char *mx_itoa(int number);

void mx_foreach(int *arr, int size, void(*f)(int));

int mx_binary_search(char **arr, int size, const char *s, int *count);

int mx_bubble_sort(char **arr, int size);

int mx_quicksort(char **arr, int left, int right);


