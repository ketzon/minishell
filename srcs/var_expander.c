/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 13:36:44 by fgonzale          #+#    #+#             */
/*   Updated: 2023/09/19 20:01:10 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int var_word_len(char *str)
{
    int i;

    i = 0;
    while (str[i] && str[i] != ' ')
        i++;
    return (i);
}

static char    *find_matching_var(t_data *data, char *word)
{
    t_var   *env_tmp;
    env_tmp = data->env_head->first_node;
    
    while (env_tmp)
    {
        if (ft_strncmp(env_tmp->name, word, var_word_len(word)) == 0)
            return (ft_strdup(env_tmp->infos));
        env_tmp = env_tmp->next;
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
            i++;
            var_value = find_matching_var(data, &node->word[i]);
            node->word = var_value;
            break ;
        }
        i++;
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