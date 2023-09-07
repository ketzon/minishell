/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 17:44:56 by fgonzale          #+#    #+#             */
/*   Updated: 2023/09/07 11:01:15 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* SAUTE LES ESPACES DANS UNE STRING ET RENVOIE DE COMBIEN IL A AVANCE */
int ft_skip_white_spaces(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0' && str[i] == ' ')
        i++;
    return (i);
}

void    stack_add_bottom(t_lexer **head, t_lexer *new)
{
    t_lexer *tmp;

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

t_lexer *new_node(char *input, t_token token, int index)
{
    t_lexer *new;

    new = malloc(sizeof(*new));
    new->i = index;
    new->next = NULL;
    new->previous = NULL;
    new->token = token;
    new->word = input;
    return (new);
}
