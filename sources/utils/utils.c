#include "utils.h"
#include <string.h>
#include <stdlib.h>



char	*strjoin(char *string1, const char *string2) {
    char		*new_str    = NULL;
    size_t		f_index     = 0;
    size_t		s_index     = 0;

    if (!string1 || !string2)
        return NULL;

    new_str = malloc(sizeof(char) * (strlen(string1) + strlen(string2) + 1));
    if (!new_str)
        return (NULL);

    if (string1)
        while (string1[f_index])
            new_str[s_index++] = string1[f_index++];
    f_index = 0;
    if (string2)
        while (string2[f_index])
            new_str[s_index++] = string2[f_index++];
    new_str[s_index] = '\0';
    free(string1);
    return (new_str);
}
