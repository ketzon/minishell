/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parse_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:55:08 by fgonzale          #+#    #+#             */
/*   Updated: 2023/12/09 20:13:27 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_token(char *input, int i, t_lexer **head)
{
	t_token	token;
	char	*str;

	if (input[i] == '\0')
	{
		str = "\0";
		token = END;
	}
	if (input[i] == '>' && input[i + 1] == '>')
	{
		str = ">>";
		token = OUTAPPEND;
	}
	else if (input[i] == '>')
	{
		str = ">";
		token = OUTPUT;
	}
	else if (input[i] == '<' && input[i + 1] == '<')
	{
		str = "<<";
		token = HEREDOC;
	}
	else if (input[i] == '<')
	{
		str = "<";
		token = INPUT;
	}
	else if (input[i] == '|')
	{
		str = "|";
		token = PIPE;
	}
	stack_add_bottom(head, new_node(str, NULL, token));
	return ;
}

void	stack_add_bottom(t_lexer **head, t_lexer *new)
{
	t_lexer	*tmp;

	if (*head == NULL)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->previous = tmp;
	}
}

t_lexer	*new_node(char *input, char *input_backup, t_token token)
{
	t_lexer	*new;

	new = malloc(sizeof(*new));
	new->next = NULL;
	new->previous = NULL;
	new->token = token;
	new->word = input;
	new->var_exists = false;
	new->join = false;
	new->word_backup = input_backup;
	return (new);
}
