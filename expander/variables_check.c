/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 19:49:54 by fgonzale          #+#    #+#             */
/*   Updated: 2023/11/16 19:58:17 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool  check_invalid_consecutive_tokens(t_lexer *node)
{
    if (node->token == PIPE && node->previous && node->previous->token == PIPE)
        return (true);
    if (node->token > PIPE && node->previous && node->previous->token > PIPE)
        return (true);
    if (node->token == END && node->previous && node->previous->token >= PIPE)
        return (true);
    return (false);
}

static bool check_invalid_tokens(t_lexer *node)
{
    if (check_invalid_consecutive_tokens(node) == true)
    {
        if (node->token == END && node->previous && node->previous->token > PIPE)
            printf("syntax error near unexpected token 'newline'\n");

        else if (node->token == END && node->previous)
            printf("syntax error near unexpected token '%s'\n", node->previous->word);
		else
			printf("syntax error near unexpected token '%s'\n", node->word);
        return (true);
    }
    return (false);
}

static void flag_variables (t_lexer *node)
{
    int i;

    i = 0;
    while (node->word[i])
    {
        if (node->word[i] == '$')
        {
			if (node->previous && node->previous->token == HEREDOC)
				break;
            node->token = VAR;
            return ;
        }
        i++;
    }
}

int variable_check(t_data *data)
{
    t_lexer *temp;

    temp = data->lexer_head;

    if (temp->token == PIPE)
        return (printf("syntax error near unexpected token '|'\n"), 1);
    while (temp)
    {
       flag_variables(temp);
       if (check_invalid_tokens(temp) == true)
            return (1);
       temp = temp->next;
    }
    return (0);
}
