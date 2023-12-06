/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parse_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:55:08 by fgonzale          #+#    #+#             */
/*   Updated: 2023/12/06 17:07:55 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	add_token(char *input, int i, t_lexer **head)
{
	t_token	token;
	char	*str;
	int		j;

	if (input[i] == '\0')
	{
		j = 0;
		str = "\0";
		token = END;
	}
	if (input[i] == '>' && input[i + 1] == '>')
	{
		j = 2;
		str = ">>";
		token = OUTAPPEND;
	}
	else if (input[i] == '>')
	{
		j = 1;
		str = ">";
		token = OUTPUT;
	}
	else if (input[i] == '<' && input[i + 1] == '<')
	{
		j = 2;
		str = "<<";
		token = HEREDOC;
	}
	else if (input[i] == '<')
	{
		j = 1;
		str = "<";
		token = INPUT;
	}
	else if (input[i] == '|')
	{
		j = 1;
		str = "|";
		token = PIPE;
	}
	stack_add_bottom(head, new_node(str, NULL, token));
	return (j);
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

int	quotes_handling(char *str, int start, char quote) // PEUT ETRE DELETE.
{
	int	i;

	i = 0;
	if (str[start] != quote)
		return (0);
	i++;
	while (str[start + i] && str[start + i] != quote)
		i++;
	return (i);
}
