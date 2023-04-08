#include "minishell.h"

char    *find_path(char *cmd, char **env_path)
{
    char    *proto_ret;
    char    *ret;
    int     i = -1;

    while (env_path[++i])
    {
        proto_ret = ft_strjoin(env_path[i], "/");
        ret = ft_strjoin(proto_ret, cmd);
        free(proto_ret);
        if (access(ret, F_OK) == 0)
            return (ret);
        free(ret);
    }
    if (access(cmd, F_OK) == 0)
         return (cmd);
    printf("aporlo%s: No such file or directory\n", cmd);
    return (NULL);
}

int     single_executor(t_system *env, t_cmd_table *cmdt, t_executor *exe)
{
    signal_operator(env, BASH_OPT);
    if ((exe->in_fd < 0 && cmdt->infile) || (exe->out_fd && cmdt->outfile))
    {
        perror("file not found\n");
        return (0);
    }
    if (cmdt->infile != NULL)
        dup2(exe->in_fd, STDIN_FILENO);
    if (cmdt->outfile != NULL)
        dup2(exe->out_fd, STDOUT_FILENO);
    tcsetattr(STDIN_FILENO, TCSANOW, env->myshell_term);
    signal_operator(env, BASH_OPT);
    exe->pid = fork();
    if (exe->pid < 0)
        return (0);
    else if (exe->pid == 0)
    {
        if (execve(find_path(cmdt->cmds->cmd_arr[0], env->env_path), cmdt->cmds->cmd_arr, NULL) < 0)
            return (0);
    }
    waitpid(-1, NULL, 0);
    tcsetattr(STDIN_FILENO, TCSANOW, env->myshell_term);
    return (1);
}
