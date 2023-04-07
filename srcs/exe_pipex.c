#include "minishell.h"

static void     close_pipes(t_executor *exe)
{
    int     i = 0;

    while (i < exe->pipe_no)
    {
        close(exe->pipe[i]);
        i++;
    }
}

static void     dup_pipes(int to_in, int to_out)
{
    if (to_in > 0)
        dup2(to_in, STDIN_FILENO);
    if (to_out > 0)
        dup2(to_out, STDOUT_FILENO);
}

static int      child_processes(t_system *env, t_cmd_node *node, t_executor *exe)
{
    exe->node_ptr++;
    exe->pid = fork();
    if (exe->pid < 0)
        return (0);
    else if (exe->pid == 0)
    {
        if (exe->node_ptr == 0)
            dup_pipes(exe->in_fd, exe->pipe[1]);
        else if (exe->node_ptr == exe->nodesize - 1)
            dup_pipes(exe->pipe[exe->node_ptr * 2 - 2], exe->out_fd);
        else
            dup_pipes(exe->pipe[exe->node_ptr * 2 - 2], exe->pipe[exe->node_ptr * 2 + 1]);
        close_pipes(exe);
        if (execve(find_path(node->cmd_arr[0], env->env_path), node->cmd_arr, NULL) < 0)
            return (0);
    }
    return (1);
}

int     pipe_executor(t_system *env, t_cmd_table *cmdt, t_executor *exe)
{
    t_cmd_node  *cmd_ptr;

    if ((exe->in_fd < 0 && cmdt->infile) || (exe->out_fd < 0 && cmdt->outfile))
    {
        perror("file not found\n");
        return (0);
    }
    cmd_ptr = cmdt->cmds;
    tcsetattr(STDIN_FILENO, TCSANOW, env->myshell_term);
    signal_operator(env, BASH_OPT);
    while (cmd_ptr)
    {
        if (child_processes(env, cmd_ptr, exe) != 1)
            return (0);
        cmd_ptr = cmd_ptr->next;
    }
    close_pipes(exe);
    waitpid(-1, NULL, 0);
    tcsetattr(STDIN_FILENO, TCSANOW, env->myshell_term);
    return (1);
}
