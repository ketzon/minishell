/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbesson <fbesson@sudent.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 18:47:29 by fbesson           #+#    #+#             */
/*   Updated: 2022/11/22 19:39:39 by fbesson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *str, void (*fonction)(unsigned int, char*))
{
	size_t	i;

	i = 0;
	if (!str || !fonction)
		return ;
	while (str[i])
	{
		fonction(i, &str[i]);
		i++;
	}
	return ;
}
