/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pingpanu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 22:24:35 by pingpanu          #+#    #+#             */
/*   Updated: 2022/03/06 12:00:16 by pingpanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	cuc;
	size_t			i;

	i = ft_strlen(s);
	cuc = (unsigned char) c;
	while (s[i] != cuc)
	{
		if (i == 0)
			return (NULL);
		i--;
	}
	return ((char *)s + i);
}
