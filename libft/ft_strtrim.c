/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbesson@student.42.fr <marvin@42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 17:05:36 by fbesson@stude     #+#    #+#             */
/*   Updated: 2022/11/19 19:29:29 by fbesson@stude    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_set_str(const char c, const char *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}	
	return (0);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	i;	
	size_t	min;	
	size_t	max;	
	char	*tab;

	i = 0;
	min = 0;
	max = ft_strlen(s1);
	while (s1[min] && ft_set_str(s1[min], set))
		min++;
	while (max > min && ft_set_str(s1[max - 1], set))
		max--;
	tab = (char *)malloc(sizeof(*s1) * max - min + 1);
	if (!tab)
		return (NULL);
	while (min < max)
	{
		tab[i++] = s1[min++];
	}	
	tab[i] = '\0';
	return (tab);
}
