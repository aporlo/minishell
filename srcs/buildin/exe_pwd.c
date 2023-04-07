#include "minishell.h"

int     exe_pwd(t_cmd_node *node)
{
    char    *path;

    if (node->cmd_arr[1])
    {
        printf("minishell pwd don't support optional cmds\n");
        return (0);
    }
    path = ft_calloc(sizeof(char), 1000);
    if (getcwd(path, 999) != NULL)
        printf("%s\n", path);
    else
    {
        perror("pwd error");
        return (1);
    }
    return (0);
}
