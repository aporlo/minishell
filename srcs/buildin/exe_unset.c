#include "minishell.h"

static int  validate_node(char *str)
{
    if (!ft_isalpha(str[0]) && str[0] != '-')
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
        if (ft_strncmp(arr[i], torem, ft_strlen(torem)))
            start = 1;
        if (start == 1)
            arr[i] = ft_strdup(arr[i + 1]);
        if (i == size)
        {
            free(arr[i]);
            arr[i] = NULL;
        }
        i++;
    }
}

int     exe_unset(t_cmd_node *node, t_system *env)
{
    int     i = 1;
    int     j = 0;

    while (node->cmd_arr[i])
    {
        if (!validate_node(node->cmd_arr[i]))
            break ;
        if (!ft_strncmp(node->cmd_arr[i], env->env_cop[j], ft_strlen(env->env_cop[j])))
            remove_char_arr(env->env_cop[j], env->env_cop);
        else
            j++;
        i++;
    }
    return (0);
}
