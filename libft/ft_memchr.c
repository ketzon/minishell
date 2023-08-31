/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbesson@student.42.fr <marvin@42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 20:07:56 by fbesson@stude     #+#    #+#             */
/*   Updated: 2022/11/22 23:00:06 by fbesson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *memoire, int value, size_t n)
{
	size_t			i;
	unsigned char	*memoire2;
	unsigned char	value2;

	memoire2 = (unsigned char *)memoire;
	value2 = (unsigned char) value;
	i = 0;
	if (!memoire || n <= 0)
		return (NULL);
	while (i < n)
	{
		if (memoire2[i] == value2)
			return (&memoire2[i]);
		i++;
	}
	return (NULL);
}
