/**
 * @file mx_string.c
 * @brief Implementation of various string manipulation functions.
 *
 * This file contains the implementation of various utility functions for
 * string manipulation, including functions for computing string length,
 * swapping characters, reversing strings, deleting strings, duplicating
 * strings, and more.
 *
 * @functions
 * - int mx_strlen(const char *s): Computes the length of a string.
 * - void mx_swap_char(char *s1, char *s2): Swaps two characters.
 * - void mx_str_reverse(char *s): Reverses a string.
 * - void mx_strdel(char **str): Deletes a string and sets the pointer to NULL.
 * - void mx_del_strarr(char ***arr): Deletes an array of strings and sets the pointer to NULL.
 * - int mx_get_char_index(const char *str, char s): Gets the index of the first occurrence of a character in a string.
 * - char *mx_strdup(const char *s1): Duplicates a string.
 * - char *mx_strndup(const char *s1, size_t n): Duplicates the first n characters of a string.
 * - char *mx_strcpy(char *dst, const char *src): Copies a string to a destination buffer.
 * - char *mx_strncpy(char *dst, const char *src, int len): Copies up to len characters of a string to a destination buffer.
 * - int mx_strcmp(const char *s1, const char *s2): Compares two strings.
 * - char *mx_strcat(char *restrict s1, const char *restrict s2): Concatenates two strings.
 * - char *mx_strstr(const char *haystack, const char *needle): Finds the first occurrence of a substring in a string.
 * - int mx_get_substr_index(const char *str, const char *sub): Gets the index of the first occurrence of a substring in a string.
 * - int mx_count_substr(const char *str, const char *sub): Counts the number of occurrences of a substring in a string.
 * - int mx_count_words(const char *str, char c): Counts the number of words in a string separated by a given character.
 * - char *mx_strnew(const int size): Allocates a new string of a given size and initializes it with null characters.
 * - char *mx_strtrim(const char *str): Trims leading and trailing whitespace from a string.
 * - char *mx_del_extra_spaces(const char *str): Removes extra spaces from a string, leaving only single spaces between words.
 * - char **mx_strsplit(const char *str, char c): Splits a string into an array of words separated by a given character.
 * - char *mx_strjoin(const char *s1, const char *s2): Joins two strings into a new string.
 * - char *mx_file_to_str(const char *file): Reads the contents of a file into a string.
 * - char *mx_replace_substr(const char *str, const char *sub, const char *replace): Replaces all occurrences of a substring in a string with another substring.
 * - int mx_read_line(char **lineptr, size_t buf_size, char delim, const int fd): Reads a line from a file descriptor.
 */

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

void mx_swap_char(char *s1, char *s2) {
    if (!(s1 && s2)) {
        return;
    }

    char temp = *s1;
    *s1 = *s2;
    *s2 = temp;
}

void mx_str_reverse(char *s) {
    if (s == NULL) {
        return;
    }

    int len = mx_strlen(s);
    for (int i = 0; i < len / 2; i++) {
        mx_swap_char(&s[i], &s[len - i - 1]);
    }
}

void mx_strdel(char **str) {
    if (str == NULL) {
        return;
    }

    free(*str);
    *str = NULL;
}

void mx_del_strarr(char ***arr) {
    if (arr == NULL || *arr == NULL) {
        return;
    }

    for (int i = 0; (*arr)[i] != NULL; i++) {
        mx_strdel(&(*arr)[i]);
    }

    free(*arr);
    *arr = NULL;
}

int mx_get_char_index(const char *str, char s) {
    if (str == NULL) {
        return -2;
    }

    for (int i = 0; i < mx_strlen(str); ++i) {
        if (s == str[i]) return i;
    }

    return -1;
}

char *mx_strdup(const char *s1) {
    if (s1 == NULL) {
        return NULL;
    }

    int len = mx_strlen(s1);

    char *res = (char*)malloc(len + 1);

    if (!res) {
        return NULL;
    }

    for (int i = 0; i <= len; ++i) {
        res[i] = s1[i];
    }

    return res;
}

char *mx_strndup(const char *s1, size_t n) {
    if (s1 == NULL) {
        return NULL;
    }

    if ((int)n > mx_strlen(s1)) n = mx_strlen(s1);

    char *res = (char*)malloc(n + 1);

    if (!res) {
        return NULL;
    }

    for (int i = 0; i < (int)n; ++i) {
        res[i] = s1[i];
    }

    res[n] = '\0';

    return res;
}

char *mx_strcpy(char *dst, const char *src) {
    if (src == NULL) {
        return NULL;
    }

    char *buf = dst;
    while (*src) {
        *dst++ = *src++;
    }

    *dst = '\0';

    return buf;
}

char *mx_strncpy(char *dst, const char *src, int len) {
    if (src == NULL || dst == NULL || len < 0) {
        return NULL;
    }

    char *buf = dst;

    
    while (len > 0 && *src) {
        *dst++ = *src++;
        len--;
    }

    
    while (len > 0) {
        *dst++ = '\0';
        len--;
    }

    return buf;
}

int mx_strcmp(const char *s1, const char *s2) {
    
    if (s1 == NULL || s2 == NULL) {
        return -2; 
    }

    
    while (*s1 && *s2) {
        if (*s1 != *s2) {
            return *s1 - *s2; 
        }
        s1++;
        s2++;
    }

    
    return *s1 - *s2; 
}


char *mx_strcat(char *restrict s1, const char *restrict s2) {
    if (s1 == NULL || s2 == NULL) {
        return NULL;
    }

    char *buf = s1;

    while (*s1) {
        s1++;
    }

    while (*s2) {
        *s1++ = *s2++;
    }

    *s1 = '\0';
    return buf;
}

char *mx_strstr(const char *haystack, const char *needle) {
    
    if (!needle || *needle == '\0') {
        return (char *)haystack;
    }

    
    while (*haystack) {
        const char *h = haystack;
        const char *n = needle;

        
        while (*h && *n && *h == *n) {
            h++;
            n++;
        }

        
        if (*n == '\0') {
            return (char *)haystack;
        }

        
        haystack++;
    }

    
    return NULL;
}


int mx_get_substr_index(const char *str, const char *sub) {
    if (str == NULL || sub == NULL) {
        return -2;
    }

    char *result = mx_strstr(str, sub);
    if (result) {
        return result - str;
    }
    
    return -1;
}

int mx_count_substr(const char *str, const char *sub) {
    if (sub == NULL || str == NULL) {
        return -1;
    }
    
    if (*sub == '\0') {
        return 0;
    }

    const char *buf = str;

    int count = 0;

    while ((buf = mx_strstr(buf, sub)) != NULL) {
        count++;
        buf++;  
    }

    return count;
}

int mx_count_words(const char *str, char c) {
    if (str == NULL) {
        return -1;
    }

    int count = 0;
    bool in_word = false;

    for (int i = 0; str[i] != '\0'; ++i) {
        if (str[i] != c && !in_word) {
            in_word = true;
            count++;
        } else if (str[i] == c) {
            in_word = false;
        }
    }

    return count;
}

char *mx_strnew(const int size) {
    if (size < 0) return NULL;
    char *res = (char *)malloc(size + 1);
    if (res == NULL) return NULL;

    for (int i = 0; i <= size; ++i) {
        res[i] = '\0';
    }

    return res;
}


bool is_space(char c) {
    return (c == ' ' || c == '\n' || c == '\t' || c == '\f');
}

char *mx_strtrim(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    int start = 0;
    int end = mx_strlen(str) - 1;
    
    

    
    while (is_space(str[start])) {
        start++;
    }

    
    while (end >= start && is_space(str[end])) {
        end--;
    }

    
    int new_len = end - start + 1;
    if (new_len <= 0) {
        return mx_strnew(0); 
    }

    
    char *trimmed_str = mx_strnew(new_len);
    if (trimmed_str == NULL) {
        return NULL;
    }

    
    for (int i = 0; i < new_len; i++) {
        trimmed_str[i] = str[start + i];
    }

    return trimmed_str;
}

char *mx_del_extra_spaces(const char *str) {
    if (str == NULL) {
        return NULL; 
    }

    int length = mx_strlen(str);
    char *result = mx_strnew(length); 

    if (result == NULL) {
        return NULL; 
    }

    int j = 0; 
    bool in_space = false; 

    for (int i = 0; i < length; i++) {
        if (!is_space((unsigned char)str[i])) {
            result[j++] = str[i];
            in_space = false;
        } else if (!in_space && j > 0) { 
            result[j++] = ' ';
            in_space = true;
        }
    }

    
    if (j > 0 && result[j - 1] == ' ') {
        result[j - 1] = '\0'; 
    } else {
        result[j] = '\0'; 
    }

    return result; 
}

char **mx_strsplit(const char *str, char c) {
    if (str == NULL) {
        return NULL; 
    }

    int word_count = mx_count_words(str, c); 
    char **result = (char **)malloc((word_count + 1) * sizeof(char *)); 

    if (result == NULL) {
        return NULL; 
    }

    int index = 0;
    int start = -1;

    for (int i = 0; str[i]; i++) {
        if (str[i] != c) {
            if (start == -1) {
                start = i; 
            }
        } else {
            if (start != -1) {
                result[index++] = mx_strndup(str + start, i - start); 
                start = -1; 
            }
        }
    }

    
    if (start != -1) {
        result[index++] = mx_strndup(str + start, mx_strlen(str) - start);
    }

    result[index] = NULL; 

    return result; 
}

char *mx_strjoin(const char *s1, const char *s2) {
    
    if (s1 == NULL && s2 == NULL) {
        return NULL;
    }
    
    
    if (s1 == NULL) {
        return mx_strdup(s2);
    }
    if (s2 == NULL) {
        return mx_strdup(s1);
    }

    
    int len1 = mx_strlen(s1);
    int len2 = mx_strlen(s2);
    
    
    char *result = mx_strnew(len1 + len2);
    if (result == NULL) {
        return NULL; 
    }

    
    mx_strcpy(result, s1);
    
    mx_strcat(result, s2);
    
    return result; 
}

char *mx_file_to_str(const char *file) {
    if (file == NULL) {
        return NULL;
    }

    int fd = open(file, O_RDONLY);

    if (fd < 0) {
        return NULL;
    }

    char buf[1];
    int len = 0;
    while (read(fd, buf, 1)) {
        len++;
    }

    close(fd);


    fd = open(file, O_RDONLY);
    if (fd < 0) {
        return NULL;
    }

    char *result = mx_strnew(len);

    if (result == NULL) {
        return NULL;
    }

    read(fd, result, len);

    close(fd);

    return result;
}

char *mx_replace_substr(const char *str, const char *sub, const char *replace) {
    if (str == NULL || sub == NULL || replace == NULL) {
        return NULL;
    }

    int sub_count = mx_count_substr(str, sub);
    if (sub_count == 0) {
        return mx_strdup(str);
    }

    int sub_len = mx_strlen(sub);
    int replace_len = mx_strlen(replace);
    int new_len = mx_strlen(str) + sub_count * (replace_len - sub_len);

    char *result = mx_strnew(new_len);
    if (result == NULL) {
        return NULL;
    }

    int i = 0;
    int j = 0;

    while (str[i]) {
        if (mx_strstr(str + i, sub) == str + i) {
            mx_strcpy(result + j, replace);
            i += sub_len;
            j += replace_len;
        } else {
            result[j++] = str[i++];
        }
    }

    return result;
}

int mx_read_line(char **lineptr, size_t buf_size, char delim, const int fd) {
    if (lineptr == NULL || buf_size == 0 || fd < 0) {
        return -2; 
    }

    
    if (*lineptr == NULL) {
        *lineptr = (char *)malloc(buf_size);
        if (*lineptr == NULL) {
            return -2; 
        }
    }

    size_t i = 0;
    char c;

    while (read(fd, &c, 1) > 0) {
        if (c == delim) { 
            break; 
        }

        (*lineptr)[i] = c; 
        i++;

        
        if (i == buf_size) {
            char *new_buf = (char *)malloc(buf_size * 2);
            if (new_buf == NULL) {
                
                return -2; 
            }

            for (size_t j = 0; j < buf_size; j++) {
                new_buf[j] = (*lineptr)[j]; 
            }
            free(*lineptr); 
            *lineptr = new_buf; 
            buf_size *= 2; 
        }
    }

    
    if (i == 0 && read(fd, &c, 1) <= 0) {
        free(*lineptr);
        *lineptr = NULL; 
        return -1; 
    }

    (*lineptr)[i] = '\0'; 

    
    if (i > 0 && (*lineptr)[i - 1] == '\n') {
        (*lineptr)[i - 1] = '\0'; 
        return i - 1; 
    }

    return i; 
}
