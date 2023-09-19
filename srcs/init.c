/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbesson <fbesson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 15:55:07 by fbesson           #+#    #+#             */
/*   Updated: 2023/09/19 09:34:19 by fbesson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*init_env(t_data data, char **env_array)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	data.env = env_array;
	(void)data;
	if (env == NULL)
		return (NULL);
	env->env_path = get_env_path(env_array);
	create_env_list(env, env_array);
	/* free_env_array(env_array); */
	return (env);
}

t_var	*init_env_var(char *name, char *infos, int id)
{
	t_var *var;

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
