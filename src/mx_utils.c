/* mx_utils.c */

#include "../inc/libmx.h"

void mx_printchar(char c)
{
    write(1, &c, 1);
}

void mx_print_unicode(wchar_t c);

void mx_printstr(const char *s);

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


