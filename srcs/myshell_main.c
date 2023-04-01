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
	t_data	data;

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
