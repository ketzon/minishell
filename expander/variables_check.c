/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 19:49:54 by fgonzale          #+#    #+#             */
/*   Updated: 2023/12/06 17:59:54 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool	check_invalid_consecutive_tokens(t_lexer *node)
{
	if (node->token == PIPE && node->previous && node->previous->token == PIPE)
		return (true);
	if (node->token > PIPE && node->previous && node->previous->token > PIPE)
		return (true);
	if (node->token == END && node->previous && node->previous->token >= PIPE)
		return (true);
	return (false);
}

static bool	check_invalid_tokens(t_lexer *node)
{
	if (check_invalid_consecutive_tokens(node) == true)
	{
		if (node->token == END && node->previous
			&& node->previous->token > PIPE)
			errmsg("syntax error near unexpected token", "newline", true);
		else if (node->token == END && node->previous)
			errmsg("syntax error near unexpected token",
				node->previous->word, true);
		else
			errmsg("syntax error near unexpected token", node->word, true);
		return (true);
	}
	return (false);
}

static void	flag_variables(t_lexer *node)
{
	int	i;

	i = 0;
	while (node->word[i])
	{
		if (node->word[i] == '$')
		{
			if (node->previous && node->previous->token == HEREDOC)
				break ;
			node->token = VAR;
			return ;
		}
		i++;
	}
}

int	variable_check(t_data *data)
{
	t_lexer	*temp;

	temp = data->lexer_head;
	if (temp->token == PIPE)
	{
		errmsg("syntax error near unexpected token", temp->word, true);
		return (1);
	}
	while (temp)
	{
		flag_variables(temp);
		if (check_invalid_tokens(temp) == true)
			return (1);
		temp = temp->next;
	}
	return (0);
}
