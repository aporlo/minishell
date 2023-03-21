/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pingpanu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 17:55:25 by pingpanu          #+#    #+#             */
/*   Updated: 2023/03/21 18:00:43 by pingpanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define _XOPEN_SOURCE 700
# include "libft.h" //already have unistd.h and stdlib.h
# include <readline/readline.h> //readline, rl_*, and add_history
# include <readline/history.h> //readline, rl_*, and add_history
# include <stdio.h> //printf
# include <fcntl.h> //open, unlink, dup, dup2, 
# include <sys/types.h> //fork
# include <sys/wait.h> //wait, waitpid, wait3, wait4
# include <sys/stat.h> //stat, lstat, and fstat
# include <sys/ioctl.h> //ioctl
# include <signal.h> //signal, sigaction, sigemptyset, sigaddset, and kill
# include <dirent.h> //opendir, readdir, and closedir
# include <errno.h> //stderror, and perror
# include <term.h>
# include <termios.h> //tc*
# define INPUT 0
# define OPERATE 1
# define OUTPUT 2

typedef struct s_system
{
	struct sigaction	act;
	struct sigaction	quit;
	char				**env_path;
	char				*dis_str;
}		t_system;

typedef struct s_cmd_node
{
	char				**cmd_arr;
	struct s_cmd_node	*next;
}		t_cmd_node;

typedef struct s_cmd_table
{
	t_cmd_node	*cmds;
	char		*infile;
	char		*outfile;
	char		*outapp;
	char		*hdoc_delim;
}	t_cmd_table;

typedef struct s_executor
{
	pid_t	pid;
	int		node_ptr;
	int		nodesize;
	int		pipe_no;
	int		*pipe;
}		t_executor;

void		lexer(t_list **cmd_ll, char *str);
t_cmd_table	*parser(t_list *cmd_ll);
int			executor(t_system my_env, t_cmd_table *cmd_table);
#endif
