/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myshell_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsomrat <lsomrat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 21:08:07 by lsomrat           #+#    #+#             */
/*   Updated: 2023/03/16 21:08:22 by lsomrat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmdtable(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}


int	main(void)
{
	// char				*cmd_str;
	// char				**cmd_table;
	// t_list				*cmd_ll;
	// t_system			my_env;
	// struct sigaction	act;
	// struct sigaction	quit;
	t_data	data;

	// *cmd_str = NULL;
	// *cmd_ll = NULL;
	// my_env.env_path = ft_split(getenv("PATH"), ':');
	// my_env.dis_str = ft_strjoin(getenv("USER"), ": ");
	// act.sa_handler = sighandler;
	// act.sa_flags = 0;
	// sigemptyset(&act.sa_mask);
	// sigaction (SIGINT, &act, NULL);
	// quit.sa_handler = SIG_IGN;
	// quit.sa_flags = 0;
	// sigemptyset(&quit.sa_mask);
	// sigaction (SIGQUIT, &quit, NULL);
	init(&data);
	while (1)
	{
		data.cmd_str = readline(data.my_env.dis_str);
		if (data.cmd_str == NULL)
			break ;
		add_history(data.cmd_str);
		printf("str is %s\n", data.cmd_str);
		lexer(&data);
		data.cmd_table = parser(data.cmd_ll);
		if (data.cmd_table)
			executor(data.my_env, data.cmd_table);
		// ft_lstclear(&data.cmd_ll);
		// free_cmdtable(data.cmd_table);
	}
	printf("exit\n");
	return (0);
}
