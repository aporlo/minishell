#include "minishell.h"

static int  check_export_str(char *str)
{
    int i = -1;
    int equal = 0;

    while (str[++i])
    {
        if (!ft_isprint(str[i]))
            return (0);
        if (str[i] == '=')
            equal++;
    }
    if (equal != 1)
        return (0);
    return (1);
}

static char **add_env(char *newenv, char **arr)
{
    int     i = 0;
    char    **ret;
    
    while (arr[i])
        i++;
    ret = ft_calloc(sizeof(char*), i + 2);
    if (!ret)
        return (NULL);
    i = -1;
    while(arr[++i])
        ret[i] = ft_strdup(arr[i]);
    ret[i] = ft_strdup(newenv);
    return (ret);
}

int     exe_export(t_cmd_node *node, t_system *env)
{
    char    *var_name;
    int     i = -1;

    if (!node->cmd_arr[1])
    {
        while (env->env_cop[++i])
        {
            var_name = ft_strjoin("declare -x ", env->env_cop[i]);
            printf("%s\n", var_name);
            free(var_name);
        }
    }
    else
    {
        if (node->cmd_arr[2])
            printf("export only support 1 arguments\n");
        else if (!check_export_str(node->cmd_arr[1]))
            printf("improper string format\n");
        else
        {
            env->env_cop = add_env(node->cmd_arr[1], env->env_cop);
            if (!env->env_cop)
                return (1);
        }
    }
    return (0);
}