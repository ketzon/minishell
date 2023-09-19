/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 13:36:44 by fgonzale          #+#    #+#             */
/*   Updated: 2023/09/19 14:01:46 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    find_matching_var(t_data *data, t_lexer *node)
{
    
}

void    replace_var(t_data *data, t_lexer *node)
{
    int i;

    i = 0;
    while (node->word[i])
    {
        if (node->word[i] == '$')
        {
            find_matching_var(data, node);
            break ;
        }
    }
}

void    variable_expander(t_data *data)
{
    t_lexer *tmp;

    tmp = data->lexer_head;
    while (tmp)
    {
        if (tmp->token == VAR)
        {
            replace_var(data, tmp);
        }
        tmp = tmp->next;
    } 
}