#include "minishell.h"

char    *find_path(char *cmd, char **env_path)
{
    char    *proto_ret;
    char    *ret;
    int     i = -1;

    /*check if argv[1] is cmd installed in the computer*/
    while (env_path[++i])
    {
        proto_ret = ft_strjoin(env_path[i], "/");
        ret = ft_strjoin(proto_ret, cmd);
        free(proto_ret);
        if (access(ret, F_OK) == 0)
            return (ret);
        free(ret);
    }
    /*when argv[1] is not cmd installed in the computer*/
    /*check if we can access the file*/
    if (access(cmd, F_OK) == 0)
        return (cmd);
    printf("%s: No such file or directory\n", cmd);
    return (NULL);
}

int     single_executor(t_system env, t_cmd_table *cmdt, t_executor *exe)
{
    char    *path;
    
    if ((exe->in_fd < 0 && cmdt->infile != NULL) || (exe->out_fd < 1 && cmdt->outfile != NULL))
    {
        perror("file not found");
        return (0);
    }
    if (cmdt->infile != NULL)
        dup2(exe->in_fd, STDIN_FILENO);
    if (cmdt->outfile != NULL)
        dup2(exe->out_fd, STDOUT_FILENO);
    exe->pid = fork();
    if (exe->pid < 0)
        return (0);
    else if (exe->pid == 0)
    {
        path = find_path(cmdt->cmds->cmd_arr[0], env.env_path);
        if (execve(path, cmdt->cmds->cmd_arr, NULL) == -1)
            //buildins(env, cmds->cmd_arr, exe);
            printf("Command not found\n");
    }
    else
        wait(NULL);
    return (1);
}