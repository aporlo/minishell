#include "libft.h"
#include <stdio.h>

t_list  *ft_lstnew(void *content)
{
    t_list  *new;

    new = malloc(sizeof(t_list));
    if (!new || !content)
        return (NULL);
    new->token = content;
    new->next = NULL;
    return (new);
}