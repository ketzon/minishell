/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbesson@student.42.fr <marvin@42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 20:08:04 by fbesson@stude     #+#    #+#             */
/*   Updated: 2022/11/29 20:14:00 by fbesson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *memoire1, const void *memoire2, size_t n)
{
	size_t			i;
	unsigned char	*memoire3;
	unsigned char	*memoire4;

	i = 0;
	memoire3 = (unsigned char *)memoire1;
	memoire4 = (unsigned char *)memoire2;
	while (i < n)
	{
		if (memoire3[i] != memoire4[i])
			return (memoire3[i] - memoire4[i]);
		i++;
	}
	return (0);
}
