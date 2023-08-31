/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbesson@student.42.fr <marvin@42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 17:26:10 by fbesson@stude     #+#    #+#             */
/*   Updated: 2022/12/01 18:14:00 by fbesson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	words_count(char const *str, char c)
{
	size_t	i;

	i = 0;
	while (*str)
	{
		while (*str && *str == c)
			str++;
		if (*str && *str != c)
			i++;
		while (*str && *str != c)
			str++;
	}
	return (i);
}

static size_t	words_lenght(char const *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

static void	clean(char **array, unsigned int nb)
{
	unsigned int	i;

	i = 0;
	while (i < nb)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

char	**ft_split(char const *str, char c)
{
	char	**array;
	size_t	i;
	size_t	w_count;
	size_t	w_len;

	i = 0;
	w_count = words_count(str, c);
	array = ((char **)malloc(sizeof(char *) * (w_count + 1)));
	if (!array)
		return (NULL);
	while (i < w_count)
	{
		w_len = words_lenght(str, c);
		if (w_len > 0)
		{
			array[i] = ft_substr(str, 0, w_len);
			if (!array[i++])
				return (clean(array, i), NULL);
		}
		str = str + w_len + 1;
	}
	array[i] = NULL;
	return (array);
}
