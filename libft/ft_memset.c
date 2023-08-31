/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbesson@student.42.fr <marvin@42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 20:08:22 by fbesson@stude     #+#    #+#             */
/*   Updated: 2022/12/01 12:32:49 by fbesson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dest, int value, size_t n)
{
	char	*start;

	start = dest;
	if (dest == NULL)
		return (NULL);
	while (n)
	{
		*start = value;
		start++;
		n--;
	}
	return (dest);
}
