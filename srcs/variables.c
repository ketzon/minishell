/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 19:49:54 by fgonzale          #+#    #+#             */
/*   Updated: 2023/09/19 13:36:09 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool  check_invalid_consecutive_tokens(t_lexer *node)
{
    if (node->token == PIPE && node->previous && node->previous->token == PIPE)
        return (true);
    if (node->token > PIPE && node->previous && node->previous->token > PIPE)
        return (true);
    if (node->token >= PIPE && node->next == NULL)
        return (true);
    return (false);
}

static bool check_invalid_tokens(t_lexer *node)
{
    if (check_invalid_consecutive_tokens(node) == true)
    {
        if (node->next == NULL && node->token > PIPE)
            printf("syntax error near unexpected token 'newline'\n"); // CHANGER PARCE QUE C'EST PAS 100% WORKING
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
    if (!node->word)
        return ;
    while (node->word[i])
    {
        if (node->word[i] == '$')
        {
            node->token = VAR;
            break ;
        }
        i++;
    }
}

int variable_check(t_data *data)
{
    t_lexer *temp;

    temp = data->lexer_head;
    
    if (temp->token == PIPE)
        return (printf("syntax error near unexpected token '|'\n"), 0);
    while (temp)
    {
       flag_variables(temp);
       if (check_invalid_tokens(temp) == true)
            return (0);
       temp = temp->next;
    }
    
    temp = data->lexer_head;
    while (temp)
    {
        if (temp->word)
            printf("%s, type = %d\n", temp->word, temp->token);
        else
            printf("%d, type = %d\n", temp->token, temp->token);
        temp = temp->next;
    }
    return (1);
}