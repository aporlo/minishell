/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsomrat <lsomrat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 13:56:01 by lsomrat           #+#    #+#             */
/*   Updated: 2023/03/17 13:56:06 by lsomrat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_quote(char ch)
{
	if (ch == '"' || ch == 39)
		return (true);
	return (false);
}

char	*sub_string(char *str, int left, int right)
{
	int		i;
	char	*sub_str;

	i = left;
	sub_str = (char *)malloc(sizeof(char) * (right - left + 2));
	while (i <= right)
	{
		sub_str[i - left] = str[i];
		i++;
	}
	sub_str[right - left + 1] = '\0';
	return (sub_str);
}

static void	add_cmd(t_stpar *stpar, t_data *data, int n)
{
	char	*substr;

	substr = NULL;
	if (n == 0)
		substr = ft_substr(data->cmd_str, stpar->l, (stpar->r - stpar->l));
	else
		substr = ft_substr(data->cmd_str, stpar->l, (stpar->r - stpar->l + 1));
	ft_lstadd_back(&data->cmd_ll, ft_lstnew(ft_strdup(substr)));
	if (n == 1)
		stpar->r++;
	stpar->l = stpar->r;
	free(substr);
}

static int	check(t_data *data, t_stpar stpar)
{
	int	space;

	space = isspace(data->cmd_str[stpar.r]);
	if ((space == 0 && is_quote(data->cmd_str[stpar.r]) == false)
		&& stpar.r < stpar.len)
		return (1);
	return (0);
}

void	lexer(t_data *data, t_stpar stpar)
{
	stpar.len = ft_strlen(data->cmd_str);
	while (stpar.r < stpar.len && stpar.l <= stpar.r)
	{
		if (isspace(data->cmd_str[stpar.r]))
		{
			stpar.r++;
			stpar.l++;
		}
		else if (is_quote(data->cmd_str[stpar.r]) == true)
		{
			stpar.quote = data->cmd_str[stpar.r];
			stpar.r++;
			while (data->cmd_str[stpar.r] != stpar.quote && stpar.r < stpar.l)
				stpar.r++;
			add_cmd(&stpar, data, 1);
		}
		else
		{
			stpar.r++;
			while (check(data, stpar) == 1)
				stpar.r++;
			add_cmd(&stpar, data, 0);
		}
	}
	expander(&data->cmd_ll);
}
