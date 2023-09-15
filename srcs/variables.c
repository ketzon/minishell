/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 19:49:54 by fgonzale          #+#    #+#             */
/*   Updated: 2023/09/15 13:11:10 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void is_there_variable (t_lexer *node)
{
    int i;

    i = 0;
    if (!node->word)
        return ;
    while (node->word[i])
    {
        if (node->word[i] == '$')
            node->token = VAR;
        i++;
    }
}

int variable_check(t_data *data)
{
    t_lexer *temp;

    temp = data->lexer_head;
    
    if (temp->token == PIPE)
        return (printf("syntax error near unexpected token |"), 0);
    while (temp)
    {
       is_there_variable(temp);
       //check_consecutive_tokens(temp);
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