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

static char	*newtoken(char *str)
{
	if (ft_strncmp(str, ">", 2) == 0)
		return (ft_strdup("GREAT"));
	else if (ft_strncmp(str, "<", 2) == 0)
		return (ft_strdup("LESS"));
	else if (ft_strncmp(str, ">>", 3) == 0)
		return (ft_strdup("GREATGREAT"));
	else if (ft_strncmp(str, "<<", 3) == 0)
		return (ft_strdup("LESSLESS"));
	else if (ft_strncmp(str, "|", 2) == 0)
		return (ft_strdup("PIPE"));
	else
		return (ft_strdup(str));
}

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

void	add_cmd(t_data *data, char *substr, int n)
{
	if (n == 0)
		substr = sub_string(data->cmd_str, data->s_left, data->s_right - 1);
	else
		substr = sub_string(data->cmd_str, data->s_left, data->s_right);
	ft_lstadd_back(&data->cmd_ll, ft_lstnew(newtoken(substr)));
	if (n == 1)
		data->s_right++;
	data->s_left = data->s_right;
	free(substr);
}

void	lexer(t_data *data)
{
	int		quote;
	char	*substr;

	substr = NULL;
	data->s_len = strlen(data->cmd_str);
	while (data->s_right < data->s_len && data->s_left <= data->s_right)
	{
		if (isspace(data->cmd_str[data->s_right]))
		{
			data->s_right++;
			data->s_left = data->s_right;
		}
		else if (is_quote(data->cmd_str[data->s_right]) == true)
		{
			quote = data->cmd_str[data->s_right];
			data->s_right++;
			while (data->cmd_str[data->s_right] != quote && data->s_right < data->s_len)
				data->s_right++;
			add_cmd(data, substr, 1);
		}
		else
		{
			data->s_right++;
			while (isspace(data->cmd_str[data->s_right]) == 0 && data->s_right < data->s_len)
				data->s_right++;
			add_cmd(data, substr, 0);
		}
	}
}
