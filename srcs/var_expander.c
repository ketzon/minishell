/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 13:36:44 by fgonzale          #+#    #+#             */
/*   Updated: 2023/09/19 14:41:31 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int var_word_len(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == ' ')
            break ;
        i++;
    }
    return (i);
}

static char    *find_matching_var(t_data *data, char *word)
{
    while (data->env_head->first_node)
    {
        if (ft_strncmp(data->env_head->first_node->name, word, var_word_len(word - 1)) == 0)
            return (data->env_head->first_node->infos);
        data->env_head->first_node = data->env_head->first_node->next;
    }
    return ("");
}

static void    replace_var(t_data *data, t_lexer *node)
{
    int i;
    char    *var_value;
    

    i = 0;
    while (node->word[i])
    {
        if (node->word[i] == '$')
        {
            var_value = find_matching_var(data, &node->word[i++]);
            free(node->word);
            node->word = var_value;
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
            printf("%s\n", tmp->word);
        }
        tmp = tmp->next;
    } 
}