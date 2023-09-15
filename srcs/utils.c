/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 17:44:56 by fgonzale          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/09/13 16:43:30 by fgonzale         ###   ########.fr       */
=======
<<<<<<< HEAD
/*   Updated: 2023/09/07 17:17:52 by fbesson          ###   ########.fr       */
>>>>>>> master
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
=======
/*   Updated: 2023/09/05 17:03:30 by fbesson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
>>>>>>> 5684930f30fb02b89ff62a932172219cabebd101

/* SAUTE LES ESPACES DANS UNE STRING ET RENVOIE DE COMBIEN IL A AVANCE */
int ft_skip_white_spaces(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0' && (str[i] == ' ' || str[i] == '\t' || str[i] == '\r'))
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

t_lexer *new_node(char *input, t_token token)
{
    t_lexer *new;

    new = malloc(sizeof(*new));
    new->next = NULL;
    new->previous = NULL;
    new->token = token;
    new->word = input;
    return (new);
}

int	whitespace(char c)
{
	return (c == ' ' || c == " " || c == '\t');
}
