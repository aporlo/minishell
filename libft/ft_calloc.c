/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pingpanu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 22:17:20 by pingpanu          #+#    #+#             */
/*   Updated: 2022/03/05 23:13:43 by pingpanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*alme;
	size_t	i;

	i = 0;
	alme = malloc (count * size);
	if (!alme)
		return (NULL);
	while (i < count * size)
	{
		alme[i] = 0;
		i++;
	}
	return (alme);
}
