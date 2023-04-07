#include "minishell.h"

int exe_echo(t_executor *exe, t_cmd_node *node)
{
    int     fd;
    int     i;

    fd = 1;
    i = 0;
    if (exe->out_fd > 0)
        fd = exe->out_fd;
    if (!ft_strncmp(node->cmd_arr[1], "-n", 3))
        i = 1;
    while (node->cmd_arr[++i])
    {
        ft_putstr_fd(node->cmd_arr[i], fd);
        ft_putchar_fd(' ', fd);
    }
    if (ft_strncmp(node->cmd_arr[1], "-n", 3))
        ft_putchar_fd('\n', fd);
    return (0);
}
