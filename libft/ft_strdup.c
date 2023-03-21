/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pingpanu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 22:22:36 by pingpanu          #+#    #+#             */
/*   Updated: 2022/02/28 22:22:38 by pingpanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*copy;
	char	*pointer;
	size_t	slen;

	slen = ft_strlen(s1);
	copy = malloc (sizeof(char) * (slen + 1));
	if (!copy)
		return (NULL);
	pointer = copy;
	while (*s1)
		*copy++ = *s1++;
	*copy = '\0';
	return (pointer);
}
