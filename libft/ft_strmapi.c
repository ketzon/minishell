/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbesson@student.42.fr <marvin@42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 23:06:31 by fbesson@stude     #+#    #+#             */
/*   Updated: 2022/11/21 00:00:17 by fbesson@stude    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*fonction)(unsigned int, char))
{
	size_t	i;
	char	*str;

	i = 0;
	str = ft_strdup(s);
	if (!str || !fonction)
		return (NULL);
	while (str[i])
	{
		str[i] = fonction(i, str[i]);
		i++;
	}
	return (str);
}
