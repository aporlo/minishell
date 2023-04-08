#include "minishell.h"

static int  validate_node(char *str)
{
    if (str[0] == '-')
    {
        printf("unset don't support optional command\n");
        return (0);
    }
    return (1);
}

static void     remove_char_arr(char *torem, char **arr)
{
    int     size;
    int     i;
    int     start;

    size = 0;
    i = 0;
    start = 0;
    while (arr[size])
        size++;
    while (arr[i])
    {
        if (i == size)
            return ;
        if (!ft_strncmp(arr[i], torem, ft_strlen(torem)))
        {
            start = i;
            free(arr[i]);
                break ;
        }
        i++;
    }
    while (arr[start + 1])
    {
        arr[start] = ft_strdup(arr[start + 1]);
        start++;
    }
    arr[start] = 0;
}

int     exe_unset(t_cmd_node *node, t_system *env)
{
    int     i = 1;

    while (node->cmd_arr[i])
    {
        if (!validate_node(node->cmd_arr[i]))
            break ;
        remove_char_arr(node->cmd_arr[i], env->env_cop);
        i++;
    }
    return (0);
}