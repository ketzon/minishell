/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 17:17:45 by fbesson           #+#    #+#             */
/*   Updated: 2023/12/09 22:37:15 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	change_status_to_quote(t_lexer **token_node, int *i, int *status)
{
	if ((*token_node)->word[*i] == '\'')
		*status = SQUOTE;
	if ((*token_node)->word[*i] == '\"')
		*status = DQUOTE;
	(*i)++;
}

static bool	if_quotes_and_default(t_lexer **token_node, int i, int *status)
{
	if (((*token_node)->word[i] == '\'' || (*token_node)->word[i] == '\"')
		&& *status == DEFAULT)
		return (true);
	else
		return (false);
}

static bool	change_back_to_default(t_lexer **token_node, int *i, int *status)
{
	if (((*token_node)->word[*i] == '\'' && *status == SQUOTE)
		|| ((*token_node)->word[*i] == '\"' && *status == DQUOTE))
	{
		*status = DEFAULT;
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
	int		status;

	i = 0;
	j = 0;
	status = DEFAULT;
	new_line = malloc(sizeof(char) * count_len((*token_node)->word, i, i));
	if (!new_line)
		return (1);
	while ((*token_node)->word[i])
	{
		if (if_quotes_and_default(token_node, i, &status) == true)
		{
			change_status_to_quote(token_node, &i, &status);
			continue ;
		}
		else if (change_back_to_default(token_node, &i, &status) == true)
			continue ;
		new_line[j++] = (*token_node)->word[i++];
	}
	new_line[j] = '\0';
	return (delete_quotes_2(token_node, new_line));
}

int	delete_quotes_2(t_lexer **token_node, char *new_line)
{
	free_reset_ptr((*token_node)->word);
	(*token_node)->word = new_line;
	(*token_node)->join = true;
	return (0);
}
