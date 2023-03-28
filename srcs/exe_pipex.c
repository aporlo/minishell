#include "minishell.h"

static void     pipe_dup(int first, int second)
{
    dup2(first, STDIN_FILENO);
    dup2(second, STDOUT_FILENO);
}

static void     close_pipes(t_executor *exe)
{
    int     i = 0;

    while (i < exe->pipe_no)
    {
        close(exe->pipe[i]);
        i++;
    }
}

int     pipe_executor(t_system env, t_cmd_table *cmdt, t_executor *exe)
{
    char        *path;
    t_cmd_node  *cmd_ptr;

    if ((exe->in_fd < 0 && cmdt->infile != NULL) || (exe->out_fd < 1 && cmdt->outfile != NULL))
    {
        perror("file not found");
        return (0);
    }
    if (cmdt->infile != NULL)
        dup2(exe->in_fd, STDIN_FILENO);
    cmd_ptr = cmdt->cmds;
    while (++exe->node_ptr < exe->nodesize)
    {
        exe->pid = fork();
        if (exe->pid < 0)
            return (0);
        else if (exe->pid == 0)
        {
            if (exe->node_ptr == 0)
                pipe_dup(exe->in_fd, exe->pipe[1]);
            else if (exe->node_ptr == exe->nodesize - 1 && cmdt->outfile)
                pipe_dup(exe->pipe[2 * exe->node_ptr - 2], exe->out_fd);
            else
                pipe_dup(exe->pipe[2 * exe->node_ptr - 2], exe->pipe[2 * exe->node_ptr + 1]);
            close_pipes(exe);
            path = find_path(cmd_ptr->cmd_arr[0], env.env_path);
            if (execve(path, cmd_ptr->cmd_arr, NULL) == -1)
                //buildins(env, cmd_ptr->cmd_arr, exe);
                printf("Command not found\n");
        }
        cmd_ptr = cmd_ptr->next;
    }
    close_pipes(exe);
    return (1);
}
