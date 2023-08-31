/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbesson@student.42.fr <marvin@42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 19:54:16 by fbesson@stude     #+#    #+#             */
/*   Updated: 2022/12/01 16:49:19 by fbesson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	digit_count(long n)
{
	int	len;

	len = 0;
	if (n == 0)
		len++;
	if (n < 0)
	{
		n = -n;
		len++;
	}
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	long	nb;
	char	*tab;
	int		len;

	nb = (long)n;
	len = digit_count(nb);
	tab = (char *)malloc(sizeof(char) * (len + 1));
	if (!tab)
		return (NULL);
	if (nb == 0)
		tab[0] = '0';
	if (nb < 0)
		nb = -nb;
	if (n < 0)
		tab[0] = '-';
	tab[len] = '\0';
		len--;
	while (nb != 0)
	{
		tab[len--] = nb % 10 + '0';
		nb = nb / 10;
	}
	return (tab);
}
