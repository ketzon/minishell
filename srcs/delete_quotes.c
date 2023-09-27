/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbesson <fbesson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 17:17:45 by fbesson           #+#    #+#             */
/*   Updated: 2023/09/27 11:09:45 by fbesson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	change_status_to_quote(t_lexer **token_node, int *i)
{
	if ((*token_node)->word[*i] == '\'')
		(*token_node)->status = SQUOTE;
	if ((*token_node)->word[*i] == '\"')
		(*token_node)->status = DQUOTE;
	(*i)++;
}

static bool	if_quotes_and_default(t_lexer **token_node, int i)
{
	if (((*token_node)->word[i] == '\'' || (*token_node)->word[i] == '\"')
		&& (*token_node)->status == DEFAULT)
		return (true);
	else
		return (false);
}

static bool	change_back_to_default(t_lexer **token_node, int *i)
{
	if (((*token_node)->word[*i] == '\'' && (*token_node)->status == SQUOTE)
		|| ((*token_node)->word[*i] == '\"' && (*token_node)->status == DQUOTE))
	{
		(*token_node)->status = DEFAULT;
		(*i)++;
		return (true);
	}
	else
		return (false);
}

int	delete_quotes(t_lexer **token_node)
{
	char	*new_line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_line = malloc(sizeof(char) * count_len((*token_node)->word, i, i));
	if (!new_line)
		return (1);
	while ((*token_node)->word[i])
	{
		if (if_quotes_and_default(token_node, i) == true)
		{
			change_status_to_quote(token_node, &i);
			continue ;
		}
		else if (change_back_to_default(token_node, &i) == true)
			continue ;
		new_line[j++] = (*token_node)->word[i++];
	}
	new_line[j] = '\0';
	/* free_ptr((*token_node)->word); */
	(*token_node)->word = new_line;
	(*token_node)->join = true;
	return (0);
}
