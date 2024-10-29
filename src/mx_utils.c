/**
 * @file mx_utils.c
 * @brief Utility functions for various operations such as printing, 
 *        mathematical calculations, and array manipulations.
 *
 * This file contains a collection of utility functions that provide 
 * basic functionalities such as printing characters, strings, and integers 
 * to the standard output, performing mathematical operations like power 
 * and square root calculations, and converting numbers between different 
 * formats. Additionally, it includes functions for sorting and searching 
 * arrays.
 *
 * Functions:
 * - void mx_printchar(char c): Prints a single character to the standard output.
 * - void mx_print_unicode(wchar_t c): Prints a Unicode character to the standard output.
 * - void mx_printstr(const char *s): Prints a string to the standard output.
 * - void mx_print_strarr(char **arr, const char *delim): Prints an array of strings with a delimiter.
 * - void mx_printint(int n): Prints an integer to the standard output.
 * - double mx_pow(double n, unsigned int pow): Calculates the power of a number.
 * - int mx_sqrt(int x): Calculates the square root of a number.
 * - char *mx_nbr_to_hex(unsigned long nbr): Converts a number to its hexadecimal string representation.
 * - unsigned long mx_hex_to_nbr(const char *hex): Converts a hexadecimal string to its numerical representation.
 * - char *mx_itoa(int number): Converts an integer to its string representation.
 * - void mx_foreach(int *arr, int size, void (*f)(int)): Applies a function to each element of an integer array.
 * - int mx_binary_search(char **arr, int size, const char *s, int *count): Performs binary search on a sorted array of strings.
 * - int mx_bubble_sort(char **arr, int size): Sorts an array of strings using bubble sort algorithm.
 * - int mx_quicksort(char **arr, int left, int right): Sorts an array of strings using quicksort algorithm.
 */

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

unsigned long mx_hex_to_nbr(const char *hex) {
    if (!hex) {
        return 0;  // Null input
    }

    unsigned long result = 0;

    for (int i = 0; hex[i] != '\0'; i++) {
        result *= 16;
        if (hex[i] >= '0' && hex[i] <= '9') {
            result += hex[i] - '0';
        } else if (hex[i] >= 'A' && hex[i] <= 'F') {
            result += hex[i] - 'A' + 10;
        } else if (hex[i] >= 'a' && hex[i] <= 'f') {
            result += hex[i] - 'a' + 10;
        } else {
            return 0;  // Invalid character in input
        }
    }

    return result;
}

char *mx_itoa(int number) {
    int temp = number;
    int len = (number <= 0) ? 1 : 0;

    while (temp) {
        temp /= 10;
        len++;
    }

    char *str = (char *)malloc(len + 1);
    if (!str) {
        return NULL;
    }

    str[len] = '\0';
    if (number == 0) {
        str[0] = '0';
        return str;
    }

    int neg = (number < 0) ? 1 : 0;
    if (neg) {
        str[0] = '-';
        number = -number;
    }

    while (number) {
        str[--len] = (number % 10) + '0';
        number /= 10;
    }

    return str;
}

void mx_foreach(int *arr, int size, void (*f)(int)) {
    if (!arr || !f) {
        return;
    }

    for (int i = 0; i < size; i++) {
        f(arr[i]);
    }
}

int mx_binary_search(char **arr, int size, const char *s, int *count) {
    if (!arr || !s || size <= 0) {
        return -1;
    }

    int left = 0;
    int right = size - 1;
    *count = 0;

    while (left <= right) {
        (*count)++;
        int mid = (left + right) / 2;
        int cmp = mx_strcmp(arr[mid], s);

        if (cmp == 0) {
            return mid;
        } else if (cmp < 0) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return -1;  // Not found
}

int mx_bubble_sort(char **arr, int size) {
    if (!arr || size <= 1) {
        return 0;
    }

    int swaps = 0;
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - 1 - i; j++) {
            if (mx_strcmp(arr[j], arr[j + 1]) > 0) {
                char *temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swaps++;
            }
        }
    }

    return swaps;
}

int mx_quicksort(char **arr, int left, int right) {
    if (!arr || left >= right) {
        return 0;
    }

    int swaps = 0;
    int pivot_index = left + (right - left) / 2;
    char *pivot = arr[pivot_index];

    int i = left;
    int j = right;

    while (i <= j) {
        while (mx_strcmp(arr[i], pivot) < 0) {
            i++;
        }
        while (mx_strcmp(arr[j], pivot) > 0) {
            j--;
        }
        if (i <= j) {
            if (i != j) {
                char *temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
                swaps++;
            }
            i++;
            j--;
        }
    }

    swaps += mx_quicksort(arr, left, j);
    swaps += mx_quicksort(arr, i, right);

    return swaps;
}
