/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsomrat <lsomrat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 13:43:57 by lsomrat           #+#    #+#             */
/*   Updated: 2023/04/06 13:43:59 by lsomrat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmdtable(t_cmd_table *cmdt)
{
	node_clear(&cmdt->cmds);
	if (cmdt->infile)
		free(cmdt->infile);
	if (cmdt->outfile)
		free(cmdt->outfile);
	free(cmdt);
}

void	free_arr(char **arr)
{
	int	i;

	if (!arr[0])
		return ;
	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

void	free_token(void *content)
{
	free(content);
}

void	node_clear(t_cmd_node **node)
{
	t_cmd_node	*prev;

	if (!node)
		return ;
	prev = *node;
	while (*node)
	{
		*node = (*node)->next;
		free_arr(prev->cmd_arr);
		free(prev);
		prev = *node;
	}
	*node = 0;
}
