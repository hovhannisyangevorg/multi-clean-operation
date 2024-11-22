#include "utils.h"
#include <string.h>
#include <stdlib.h>


char*   strjoin(char const* s1, char const* s2) {
    size_t	i;
    size_t	j;
    char	*str;

    if (!s1 || !s2)
        return (0);
    str = (char *)malloc(sizeof(*s1) * (strlen(s1) + strlen(s2) + 1));
    if (!str)
        return (0);
    i = 0;
    j = 0;
    while (s1[i])
        str[j++] = s1[i++];
    i = 0;
    while (s2[i])
        str[j++] = s2[i++];
    str[j] = '\0';
    return (str);
}
