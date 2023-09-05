/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbesson <fbesson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:26:07 by fbesson           #+#    #+#             */
/*   Updated: 2023/09/05 10:26:32 by fbesson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_quotes(int i, char *str, char del)
{
	int	j;

	j = 0;
	if (str && str[i + j] == del)
	{
		j++;
		while (str[i + j] != del && str[i + j])
			j++;
	}
	return (j);
}

int	find_matching_quote(char *line, int i, int *num_del, int del)
{
	int	j;

	j = i + 1;
	*num_del += 1;
	while (line[j] && line[j] != del)
		j++;
	if (line[j] == del)
		*num_del += 1;
	return (j - i);
}

int	count_quotes(char *line)
{
	int	i;
	int	s;
	int	d;

	s = 0;
	d = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\"')
			i += find_matching_quote(line, i, &d, '\"');
		if (line[i] == '\'')
			i += find_matching_quote(line, i, &s, '\'');
		if (line[i])
			i++;
	}
	if ((d > 0 && d % 2 != 0) || (s > 0 && s % 2 != 0))
		return (0);
	return (1);
}
