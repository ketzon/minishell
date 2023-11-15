/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:37:39 by fbesson           #+#    #+#             */
/*   Updated: 2023/11/15 13:40:14 by fbesson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_data(t_data *data, bool clear_history)
{
	if (data)
	{
		if (data->line)
			free(data->line);
		if (data->env && *data->env)
			free_env_array(data->env);
		if (data->env_head)
			free_env_struct(data->env_head);
		if (clear_history == true)
			rl_clear_history();
		//free	lexer_head;
		//free	cmd_head;
		//free	historique;
	}
}

void	free_env_struct(t_var *env_head)
{
	t_var	*tmp;

	if (!env_head)
		return ;
	while (env_head)
	{
		tmp = env_head->next;
		free(env_head->name);
		free(env_head->infos);
		free(env_head);
		env_head = tmp;
	}
}

void	free_env_array(char **env_arr)
{
	int index;

	index = 0;
	if (env_arr == NULL)
		return ;
	while (env_arr[index] != NULL)
	{
		free(env_arr[index]);
		env_arr[index] = NULL;
		index++;
	}
	free(env_arr);
	return ;
}
