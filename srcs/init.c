/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsomrat <lsomrat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 17:03:21 by lsomrat           #+#    #+#             */
/*   Updated: 2023/03/23 17:03:23 by lsomrat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sighandler(int signal)
{
	if (signal == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	init(t_data *data)
{
	data->cmd_str = NULL;
	data->cmd_ll = NULL;
	data->l = 0;
	data->r = 0;
	data->my_env.env_path = ft_split(getenv("PATH"), ':');
	data->my_env.dis_str = ft_strjoin(getenv("USER"), "@Myshell: ");
	data->my_env.act.sa_handler = sighandler;
	data->my_env.act.sa_flags = 0;
	sigemptyset(&data->my_env.act.sa_mask);
	sigaction (SIGINT, &data->my_env.act, NULL);
	data->my_env.quit.sa_handler = SIG_IGN;
	data->my_env.quit.sa_flags = 0;
	sigemptyset(&data->my_env.quit.sa_mask);
	sigaction (SIGQUIT, &data->my_env.quit, NULL);
}
