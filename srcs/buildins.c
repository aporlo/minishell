#include "minishell.h"

int is_buildins(char *cmd)
{
    if (!ft_strncmp(cmd, "echo", 5) || !ft_strncmp(cmd, "cd", 3) ||
        !ft_strncmp(cmd, "pwd", 4) || !ft_strncmp(cmd, "export", 7) ||
        !ft_strncmp(cmd, "unset", 6) || !ft_strncmp(cmd, "env", 4) ||
        !ft_strncmp(cmd, "exit", 5))
        return (1);
    return (0);
}

int buildins(t_system *env, t_cmd_table *cmdt, t_executor *exe, t_list *cmdll)
{
    t_cmd_node  *node;

    node = cmdt->cmds;
    signal_operator(env, BASH_IN);
    if (!ft_strncmp(node->cmd_arr[0], "echo", 5))
        return (exe_echo(exe, node));
    if (!ft_strncmp(node->cmd_arr[0], "cd", 3))
        return (exe_cd(env, node->cmd_arr[1]));
    if (!ft_strncmp(node->cmd_arr[0], "pwd", 4))
        return (exe_pwd(node));
    if (!ft_strncmp(node->cmd_arr[0], "export", 7))
        return (exe_export(node, env));
    if (!ft_strncmp(node->cmd_arr[0], "unset", 6))
        return (exe_unset(node, env));
    if (!ft_strncmp(node->cmd_arr[0], "env", 4))
        return (exe_env(env, node));
    if (!ft_strncmp(node->cmd_arr[0], "exit", 5))
        exit_shell(env, cmdt, cmdll, 0);
    return (0);
}
