/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 15:55:07 by fbesson           #+#    #+#             */
/*   Updated: 2023/12/09 21:09:12 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_var	*init_env(char **env_array)
{
	t_var	*env_head;

	env_head = NULL;
	create_env_list(&env_head, env_array);
	return (env_head);
}

char	*malloc_each_line(char *line)
{
	int		index;
	char	*line_malloc;

	index = 0;
	line_malloc = malloc(sizeof(char) * (ft_strlen(line) + 1));
	while (line[index] != '\0')
	{
		line_malloc[index] = line[index];
		index++;
	}
	line_malloc[index] = '\0';
	return (line_malloc);
}

char	**create_env_arr(char **envp)
{
	int		len;
	int		index;
	char	**arr;

	index = 0;
	len = line_count(envp);
	arr = malloc(sizeof(char *) * (len + 1));
	if (!arr)
		return (NULL);
	while (envp && envp[index])
	{
		arr[index] = malloc_each_line(envp[index]);
		index++;
	}
	arr[index] = '\0';
	return (arr);
}

bool	set_env_var(t_data *data, char *key, char *value)
{
	int		idx;
	char	*tmp;

	idx = get_env_var_index(data->env, key);
	if (value == NULL)
		value = "";
	tmp = ft_strjoin("=", value);
	if (!tmp)
		return (false);
	if (idx != -1 && data->env[idx])
	{
		free_ptr(data->env[idx]);
		data->env[idx] = ft_strjoin(key, tmp);
	}
	else
	{
		idx = line_count(data->env);
		data->env = realloc_env_vars(data, idx + 1);
		if (!data->env)
			return (false);
		data->env[idx] = ft_strjoin(key, tmp);
	}
	free_ptr(tmp);
	return (true);
}

t_var	*init_env_var(char *name, char *infos, int id)
{
	t_var	*var;

	var = malloc(sizeof(t_var));
	if (var == NULL)
		return (NULL);
	var->id = id;
	var->index = -1;
	var->name = name;
	var->infos = infos;
	var->next = NULL;
	var->prev = NULL;
	return (var);
}
