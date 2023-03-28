#include "minishell.h"

int     nodesize(t_cmd_node *cmds)
{
    t_cmd_node  *ptr;
    int         i = 0;

    ptr = cmds;
    while (ptr)
    {
        i++;
        ptr = ptr->next;
    }
    return (i);
}

void    init_exe(t_executor *exe, t_cmd_table *cmd_table)
{
    int     pipe_ptr = -1;

    printf("infile %s\n",cmd_table->infile);
    exe->in_fd = open(cmd_table->infile, O_RDONLY);
    printf("in_fd %d\n", exe->in_fd);
    if (!ft_strncmp(cmd_table->outfile, ">>", 2))
    {
        printf("aporlo\n");
        exe->out_fd = open(ft_strtrim(cmd_table->outfile, "> :"), O_CREAT | O_RDWR | O_APPEND, 0644);
    }
    else
        exe->out_fd = open(ft_strtrim(cmd_table->outfile, "> :"), O_CREAT | O_RDWR | O_TRUNC, 0644); 
    exe->node_ptr = -1;
    exe->nodesize = nodesize(cmd_table->cmds);
    exe->pipe_no = 2 * (exe->nodesize - 1);
    if (exe->pipe_no > 0)
    {
        exe->pipe = (int*)malloc(sizeof(int) * exe->pipe_no);
        while (++pipe_ptr < exe->nodesize - 1)
            pipe(exe->pipe + 2 * pipe_ptr);
    }
}

int     executor(t_system my_env, t_cmd_table *cmd_table)
{
    t_executor  exe;

    init_exe(&exe, cmd_table);   
    signal_operator(&my_env, BASH_IN);
    printf("pipe no = %d\n", exe.pipe_no);
    if (exe.pipe_no > 0)
    {
        if (pipe_executor(my_env, cmd_table, &exe) < 1)
            return (0);
    }
    else
    {
        if (single_executor(my_env, cmd_table, &exe) < 1)
            return (0);
    }
    signal_operator(&my_env, BASH_OUT);
    return (1);
}