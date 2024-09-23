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

void mx_print_strarr(char **arr, const char *delim);

void mx_printint(int n);

double mx_pow(double n, unsigned int pow);

int mx_sqrt(int x);

char *mx_nbr_to_hex(unsigned long nbr);

unsigned long mx_hex_to_nbr(const char *hex);

char *mx_itoa(int number);

void mx_foreach(int *arr, int size, void(*f)(int));

int mx_binary_search(char **arr, int size, const char *s, int *count);

int mx_bubble_sort(char **arr, int size);

int mx_quicksort(char **arr, int left, int right);


