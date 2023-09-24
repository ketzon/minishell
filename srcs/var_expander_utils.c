/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expander_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 15:26:40 by fgonzale          #+#    #+#             */
/*   Updated: 2023/09/24 17:45:11 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool    var_exist(t_data *data, char *var_name)
{
    t_var   *env_tmp;

    env_tmp = data->env_head->first_node;
    while (env_tmp)
    {
        if (ft_strncmp(env_tmp->name, var_name, var_word_len(var_name)) == 0)
            return (true);
        env_tmp = env_tmp->next;
    }
    return (false);
}

char     *get_var_value(t_data *data, char *var_name)
{
    t_var   *env_tmp;

    env_tmp = data->env_head->first_node;
    while (env_tmp)
    {
        if (ft_strncmp(env_tmp->name, var_name, var_word_len(var_name)) == 0)
            return (ft_strdup(env_tmp->infos));
        env_tmp = env_tmp->next;
    }
    return (NULL);
}

int var_word_len(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (isalnum(str[i]) == 0)
            break;
        i++;
    }
    return (i);
}

bool    var_in_quotes(char *word, int i)
{
    if (i > 0)
    {
        if (word[i - 1] == '\"' && word[i + 1] == '\"')
            return (true);
        else if (word[i - 1] == '\'' && word[i + 1] == '\'')
            return (true);
    }
    return (false);
}

void    quotes_check(int *single_quote, int *double_quote, char c)
{
    if (c == '\"')
        *double_quote = 1;
    else if (c == '\'')
        *single_quote = 1;
    return ;
}