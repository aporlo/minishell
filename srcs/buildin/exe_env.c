#include "minishell.h"

int         exe_env(t_system *env, t_cmd_node *node)
{
    int     i;

    i = -1;
    if (node->cmd_arr[1])
    {
        printf("minishell env don't support optional cmds\n");
        return (0);
    }
    while (env->env_path[++i])
    {
        if (!printf("%s\n", env->env_path[i]))
            return (1);
    }
    return (0);
}
