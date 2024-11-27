#include "utils.h"
#include <string.h>
#include <stdlib.h>

static size_t	ft_err_strlen(const char *string) {
    size_t	index;

    index = 0;
    if (!string)
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

    new_str = malloc(sizeof(char) * (ft_err_strlen(f_string) + ft_err_strlen(s_string) + 1));
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
