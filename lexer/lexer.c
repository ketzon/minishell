/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 10:52:58 by fgonzale          #+#    #+#             */
/*   Updated: 2023/11/13 17:23:50 by fgonzale         ###   ########.fr       */
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
    char    *str;
    int j;

	if (input[i] == '\0')
	{
		j = 0;
		str = "";
		token = END;
	}
    if (input[i] == '>' && input[i + 1] == '>')
    {
        j = 2;
        str = ">>";
        token = GREATER_DOUBLE;
    }
    else if (input[i] == '>')
    {
        j = 1;
        str = ">";
        token = GREATER;
    }
    else if (input[i] == '<' && input[i + 1] == '<')
    {
        j = 2;
        str = "<<";
        token = LESS_DOUBLE;
    }
    else if (input[i] == '<')
    {
        j = 1;
        str = "<";
        token = LESS;
    }
    else if (input[i] == '|')
    {
        j = 1;
        str = "|";
        token = PIPE;
    }
    stack_add_bottom(head, new_node(str, token));
    return (j);
}

int     add_word(char *input, int i, t_lexer **head)
{
    int j;

    j = 0;
    while (input[i + j] && !is_token(input[i + j]))
    {
        j += quotes_handling(input, i + j, 34);
        j += quotes_handling(input, i + j, 39);
        if (input[i + j] == ' ' || input[i + j] == '\0')
            break;
        else
            j++;
    }
    stack_add_bottom(head, new_node(ft_substr(input, i, j), WORD));
    return (j);
}

int quotes_handling(char *str, int start, char quote)
{
    int i;

    i = 0;
    if (str[start] != quote)
        return (0);
    i++;
    while (str[start + i] && str[start + i] != quote)
        i++;
    return (i);
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
	if (input[i] == '\0')
		add_token(input, i, &head);
    return (head);
}

void    lexer(t_data *data)
{
    char    *input;

    data->lexer_head = NULL;
    input = data->line;
    data->lexer_head = fill_lexer_struct(input);
}
