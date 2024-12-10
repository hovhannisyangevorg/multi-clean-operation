#include "utils.h"
#include <string.h>
#include <stdlib.h>

size_t	err_strlen(const char *string) {
    size_t	index;

    index = 0;
    if (string == NULL)
        return (0);
    while (string[index])
        ++index;
    return (index);
}

char	*strjoin(char *f_string, const char *s_string)
{
    char		*new_str;
    size_t		f_index;
    size_t		s_index;

    new_str = malloc(sizeof(char) * (err_strlen(f_string) + err_strlen(s_string) + 1));
    if (!new_str)
        return (NULL);
    f_index = 0;
    s_index = 0;
    if (f_string)
        while (f_string[f_index])
            new_str[s_index++] = f_string[f_index++];
    f_index = 0;
    if (s_string)
        while (s_string[f_index])
            new_str[s_index++] = s_string[f_index++];
    new_str[s_index] = '\0';
    free(f_string);
    return (new_str);
}

static int nbrlen(int n) {
    int i = 0;
    if (n <= 0) // Account for the '-' sign or '0'
        i++;
    while (n) {
        n /= 10;
        ++i;
    }
    return i;
}

char *itoa(int n) {
    int numlen = nbrlen(n);
    char *str = (char *)malloc(sizeof(char) * (numlen + 1));
    if (!str)
        return NULL;

    str[numlen] = '\0';
    unsigned int num = (n < 0) ? -n : n; // Handle negatives safely

    if (n < 0) {
        str[0] = '-';
    }
    if (n == 0) {
        str[0] = '0';
    }
    while (num) {
        str[--numlen] = (num % 10) + '0';
        num /= 10;
    }
    return str;
}
