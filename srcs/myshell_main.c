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

char	*curr_dir(void)
{
	char	pwd[1000];
	char	*ret;

	if (!getcwd(pwd, 999))
		return (NULL);
	ret = ft_strrchr(pwd, '/', 1);
	return (ret);
}

void	exit_shell(t_system *env, t_cmd_table *cmdt, t_list *cmdll, int s)
{
	if (s != 0)
		perror("Myshell");
	if (cmdt)
		free_cmdtable(cmdt);
	if (cmdll)
		ft_lstclear(&cmdll, &free_token);
	free(env->myshell_term);
	free_arr(env->env_cop);
	free_arr(env->env_path);
	rl_clear_history();
	printf("exit\n");
	exit(s);
}

int	main(int ac, char **av, char **ev)
{
	t_data	data;
	t_stpar stpar;

	if (ac != 1 || av[1])
	{
		printf("Myshell supposed to run without args\n");
		exit(1);
	}
	init(&data, ev);
	init_terminal(&data.my_env);
	init_stpar(&stpar);
	while (1)
	{
		data.cmd_str = readline((char *)data.my_env.dis_str);
		if (data.cmd_str == NULL)
			break ;
		add_history(data.cmd_str);
		lexer(&data, stpar);
		data.cmd_table = parser(data.cmd_ll);
		if (data.cmd_table)
			executor(&data.my_env, data.cmd_table, data.cmd_ll);
		free_cmdtable(data.cmd_table);
		ft_lstclear(&data.cmd_ll, &free_token);
	}
	exit_shell(&data.my_env, NULL, NULL, 0);
	return (0);
}
