/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expander_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 15:26:40 by fgonzale          #+#    #+#             */
/*   Updated: 2023/12/06 23:07:23 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	invalid_next_char(char c)
{
	if (c == ' ' || c == '\0' || c == '$')
		return (true);
	else
		return (false);
}

bool	var_exist(t_data *data, char *var_name)
{
	t_var	*env_tmp;
	size_t	var_name_len;

	if (is_index(data->env, var_name) == -1)
		return (false);
	var_name_len = ft_strlen(var_name);
	env_tmp = data->env_head;
	while (env_tmp)
	{
		if (ft_strncmp(env_tmp->name, var_name, var_name_len) == 0
			&& ft_strlen(env_tmp->name) == var_name_len)
			return (true);
		env_tmp = env_tmp->next;
	}
	return (false);
}

char	*get_var_value(t_data *data, char *var_name)
{
	t_var	*env_tmp;

	env_tmp = data->env_head;
	while (env_tmp)
	{
		if (ft_strncmp(env_tmp->name, var_name, var_word_len(var_name)) == 0)
			return (ft_strdup(env_tmp->infos));
		env_tmp = env_tmp->next;
	}
	return (NULL);
}

int	var_word_len(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '?')
		return (1);
	while (str[i])
	{
		if (isalnum(str[i]) == 0 && str[i] != '_')
			break ;
		i++;
	}
	return (i);
}

bool	var_in_quotes(char *word, int i)
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
