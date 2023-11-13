/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 15:55:07 by fbesson           #+#    #+#             */
/*   Updated: 2023/11/13 19:32:04 by fgonzale         ###   ########.fr       */
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
