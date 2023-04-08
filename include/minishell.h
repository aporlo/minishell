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
# include <stdio.h> //printf
# include <stdbool.h>
# include <stdio.h>
# include <string.h>
# include <ctype.h>
# include "libft.h" //already have unistd.h and stdlib.h
# include <readline/readline.h> //readline, rl_*, and add_history
# include <readline/history.h> //readline, rl_*, and add_history
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
# define BASH_IN 0
# define BASH_OPT 1
# define BASH_OUT 2

typedef struct s_system
{
	struct sigaction	act;
	struct sigaction	quit;
	struct termios		*myshell_term;
	char				**env_cop;
	char				**env_path;
	char				*dis_str[500];
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
	int		in_fd;
	int		out_fd;
}		t_executor;

typedef struct s_data
{
	t_cmd_table		*cmd_table;
	char			*cmd_str;
	t_list			*cmd_ll;
	t_system		my_env;
	t_executor		*exe;
}	t_data;

typedef struct s_stpar
{
	int	len;
	int	l;
	int	r;
	int	quote;
}	t_stpar;

void		sighandler(int signal);
void		exit_shell(t_system *env, t_cmd_table *cmdt, t_list *cmdll, int s);
char		*curr_dir(void);
void		lexer(t_data *data, t_stpar stpar);
void		free_token(void *content);
void		free_arr(char **arr);
void		free_cmdtable(t_cmd_table *cmdt);

t_cmd_table	*parser(t_list *cmd_ll);
char		**ll_to_strarr(t_list *cmd_ll);
t_list		*sub_linklist(t_list *left, t_list *right);
int			isredirection(t_list *ptr);
void		redirection_parse(t_list *ptr, t_cmd_table *cmd_table);
void		expander(t_list **cmd_ll);

int			executor(t_system *my_env, t_cmd_table *cmd_table, t_list *cmdll);
char		*find_path(char *cmd, char **env_path);
void		signal_operator(t_system *my_env, int status);
int			single_executor(t_system *env, t_cmd_table *cmdt, t_executor *exe);
int			pipe_executor(t_system *env, t_cmd_table *cmdt, t_executor *exe);
void		init(t_data *data, char **ev);
void		init_terminal(t_system *env);
void		init_stpar(t_stpar *stpar);
void		node_clear(t_cmd_node **node);
int			is_buildins(char *cmd);
int			buildins(t_system *env, t_cmd_table *cmdt, t_executor *exe, t_list *cmdll);
int			exe_cd(t_system *env, char *path);
int			exe_echo(t_executor *exe, t_cmd_node *node);
int			exe_env(t_system *env, t_cmd_node *node);
int			exe_pwd(t_cmd_node *node);
int			exe_unset(t_cmd_node *node, t_system *env);
int			exe_export(t_cmd_node *node, t_system *env);
#endif
