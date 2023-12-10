/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parse_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:55:08 by fgonzale          #+#    #+#             */
/*   Updated: 2023/12/10 17:12:30 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_token_part1(char *input, t_lexer **head, t_token *token, char **str)
{
	int	i;

	(void)head;
	i = 0;
	if (input[i] == '\0')
	{
		*str = "\0";
		*token = END;
	}
	if (input[i] == '>' && input[i + 1] == '>')
	{
		*str = ">>";
		*token = OUTAPPEND;
	}
	else if (input[i] == '>')
	{
		*str = ">";
		*token = OUTPUT;
	}
}

void	add_token_part2(char *input, t_lexer **head, t_token *token, char **str)
{
	int	i;

	i = 0;
	if (input[i] == '<' && input[i + 1] == '<')
	{
		*str = "<<";
		*token = HEREDOC;
	}
	else if (input[i] == '<')
	{
		*str = "<";
		*token = INPUT;
	}
	else if (input[i] == '|')
	{
		*str = "|";
		*token = PIPE;
	}
	stack_add_bottom(head, new_node(*str, NULL, *token));
}

void	add_token(char *input, int i, t_lexer **head)
{
	t_token	token;
	char	*str;

	add_token_part1(&input[i], head, &token, &str);
	add_token_part2(&input[i], head, &token, &str);
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
