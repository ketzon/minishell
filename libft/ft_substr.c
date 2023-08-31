/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbesson@student.42.fr <marvin@42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 14:46:42 by fbesson@stude     #+#    #+#             */
/*   Updated: 2022/12/01 16:17:09 by fbesson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_malloc_substr(unsigned int start, size_t n, size_t lenstr)
{
	char	*substr;

	if (start > lenstr)
	{
		substr = malloc(1);
		substr[0] = '\0';
		return (substr);
	}
	else if (start + n > lenstr)
		substr = malloc((lenstr - start + 1) * sizeof(char));
	else
		substr = malloc((n + 1) * sizeof(char));
	return (substr);
}

char	*ft_substr(char const *str, unsigned int start, size_t n)
{
	size_t	i;
	size_t	lenstr;
	char	*substr;

	i = 0;
	lenstr = ft_strlen(str);
	substr = ft_malloc_substr(start, n, lenstr);
	if (!str || !substr)
		return (NULL);
	while (start < lenstr && i < n)
		substr[i++] = str[start++];
	substr[i] = '\0';
	return (substr);
}
