/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 10:52:58 by fgonzale          #+#    #+#             */
/*   Updated: 2023/09/07 11:03:14 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool    is_token(char c)
{
    int i;
    int    tokens[3][2] = {
    {'>', 1},
    {'<', 2},
    {'|', 3},
    };

    i = 0;
    while (i < 3)
    {
        if ((int)c == tokens[i][0])
            return (true);
        i++;
    }
    return (false);
}

int    add_token(char *input, int i, t_lexer **head)
{
    t_token token;
    int j;

    if (input[i] == '>' && input[i + 1] == '>')
    {
        j = 2;
        token = GREATER_DOUBLE;
    }
    else if (input[i] == '>')
    {
        j = 1;
        token = GREATER;
    }
    else if (input[i] == '<' && input[i + 1] == '<')
    {
        j = 2;
        token = LESS_DOUBLE;
    }
    else if (input[i] == '<')
    {
        j = 1;
        token = LESS;
    }
    else if (input[i] == '|')
    {
        j = 1;
        token = PIPE;
    }
    stack_add_bottom(head, new_node(NULL, token, i));
    return (j);
}

int     add_word(char *input, int i, t_lexer **head)
{
    int j;

    j = i;
    while (input[j] && input[j] != ' ')
        j++;
    stack_add_bottom(head, new_node(ft_substr(input, i, (j - i)), 0, i));
    return (j - i);
}

t_lexer   *fill_lexer_struct(char *input)
{
    int i;
    t_lexer *head;

    head = NULL;    
    i = 0;
    while (input[i])
    {
        i += ft_skip_white_spaces(&input[i]);
        if (is_token(input[i]))
            i += add_token(input, i, &head);
        else
            i += add_word(input, i, &head);
    }
    return (head);
}

void    lexer(t_data *data, char *argv)
{
    char    *input;
    t_lexer *tmp;
    
    data->lexer_head = NULL;
    input = argv;
    data->lexer_head = fill_lexer_struct(input);
    tmp = data->lexer_head;
    while (tmp)
    {
         if (tmp->word)
             printf("%s\n", tmp->word);
         else if (tmp->token)
             printf("%d\n", tmp->token);
         tmp = tmp->next;
    }
}