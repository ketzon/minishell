/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbesson <fbesson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 15:55:07 by fbesson           #+#    #+#             */
/*   Updated: 2023/09/16 12:28:13 by fbesson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*init_env(char **env_array)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (env == NULL)
		return (NULL);
	env->env_path = get_env_path(env_array);
	env->env_vars = NULL;
	create_env_list(env, env_array);
	free_env_array(env_array);
	/* g_env = env; */
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
