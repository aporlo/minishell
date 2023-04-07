#include "minishell.h"

static int  check_export_str(char *str)
{
    int i = -1;

    while (str[++i])
    {
        // if (str[i] == '[' && str[i + 1] != '=')
        if (str[i] == '[')
            return (0);
        if (!ft_isalpha(str[i]) && !ft_isalnum(str[i]) && str[i] != '=')
            return (0);
        if (i == (int)ft_strlen(str) && str[i] == ']')
            return (0);
    }
    return (1);
}

static char *get_varname(char *str)
{
    int     i = 0;
    char    *name;

    while(str[i] != '[')
        i++;
    name = ft_calloc(i + 1, sizeof(char));
    if (!name)
        return (NULL);
    i = 0;
    while (str[i] != '[' && str[i] != '=')
    {
        name[i] = str[i];
        i++;
    }
    return (name);
}

static char **add_env(char *name, char *value, char **arr)
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
    ret[i] = ft_strjoin(name, "=");
    ret[i] = ft_strjoin(ret[i], value);
    return (ret);
}

int     exe_export(t_cmd_node *node, t_system *env)
{
    char    *var_name;
    char    *var_value;
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
            // printf("check = %d\n", check_export_str(node->cmd_arr[1]));
        else
        {
            var_name = get_varname(node->cmd_arr[1]);
            var_value = ft_strchr(node->cmd_arr[1], '=');
            printf("v_name is %s\n", var_name);
            printf("v_value is %s\n", var_value);
            env->env_cop = add_env(var_name, var_value, env->env_cop);
            free(var_name);
            if (!env->env_cop)
                return (1);
        }
    }
    return (0);
}
