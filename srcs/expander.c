#include "minishell.h"

static int      get_numdoll(char *str)
{
    int     i;

    i = 0;
    while(*str)
    {
        if (*str == '$')
            i++;
        str++;
    }
    return (i);
}

static char     *ll_to_string(t_list *buf)
{
    t_list  *ptr;
    char    *buenv;
    char    *ret;

    ptr = buf;
    ret = NULL;
    while (ptr)
    {
        buenv = (char*)ptr->token;
        if (buenv[0] == '$')
            buenv = getenv(buenv + 1);
        if (!ret)
            ret = ft_strdup(buenv);
        else
            ret = ft_strjoin(ret, buenv);
        ptr = ptr->next;
    }
    return (ret);
}

static char     *expand_dollar(char *cast)
{
    int     left = 0, right = 0;
    int     len = ft_strlen(cast);
    t_list  *buf = NULL;
    char    *substr;

    while (right <= len && left <= right)
    {
        if (right == 0 && cast[right] == '$')
            right++;
        if (cast[right] == 32)
        {
            right++;
            left++;
        }
        if ((right != 0 && cast[right] == '$') || (cast[left] == '$' && right == len))
        {
            substr = ft_substr(cast, left, (right - left));
            ft_lstadd_back(&buf, ft_lstnew(substr));
            left = right;
        }
        right++;
    }
    cast = ll_to_string(buf);
    ft_lstclear(&buf, &free_token);
    return (cast);
}

static char     *quote_remove(void *content)
{
    char    *casted;
    char    *ret;
    int     i = 0;

    casted = (char*)content;
    ret = ft_calloc(sizeof(char), ft_strlen(casted) - 1);
    while (i < (int)ft_strlen(casted) - 2)
    {
        ret[i] = casted[i + 1];
        i++;
    }
    return (ret);
}

void    expander(t_list **cmd_ll)
{
    t_list  *ptr;
    char    *casted;

    if (!(*cmd_ll))
        return ;
    ptr = *cmd_ll;
    while (ptr)
    {
        casted = (char*)ptr->token;
        if (casted[0] == 39)
            ptr->token = (void*)quote_remove(ptr->token);
        if (casted[0] == 34 && get_numdoll(casted) > 0)
        {
            casted = quote_remove(casted);
            ptr->token = (void*)expand_dollar(casted);
        }
        if (get_numdoll(casted) > 0)
            ptr->token = (void*)expand_dollar(casted);
        ptr = ptr->next;
    }
}