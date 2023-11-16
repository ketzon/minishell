/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:26:07 by fbesson           #+#    #+#             */
/*   Updated: 2023/11/15 00:17:35 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

bool closed_quotes(char *line)
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
	if (d > 0 && d % 2 != 0)
		return (printf("minishell: unexpected EOF while looking for matching : \" \n"), false);
	if (s > 0 && s % 2 != 0)
		return (printf("minishell: unexpected EOF while looking for matching : \'\n"), false);
	return (true);
}
