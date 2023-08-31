/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbesson@student.42.fr <marvin@42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 20:10:03 by fbesson@stude     #+#    #+#             */
/*   Updated: 2022/11/29 22:37:02 by fbesson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *src, const char *to_find, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 1;
	if (*to_find == '\0')
		return ((char *)src);
	while (src[i] && i < n)
	{
		if (src[i] == to_find[0])
		{
			while (src[i + j] == to_find[j] && to_find[j] && (i + j) < n)
			{
				j++;
			}
			if (to_find[j] == '\0')
				return ((char *)&src[i]);
		}		
		i++;
	}
	return (NULL);
}
