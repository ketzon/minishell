/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:37:39 by fbesson           #+#    #+#             */
/*   Updated: 2023/11/17 16:10:10 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_reset_ptr(void	*ptr)
{
	if (ptr)
		free(ptr);
	ptr = NULL;
}

void	free_data(t_data *data)
{
	if (data)
	{
		if (data->line)
			free_reset_ptr(data->line);
		if (data->env && *data->env)
			free_env_array(data->env);
		if (data->env_head)
			free_env_struct(data->env_head);
		if (data->lexer_head)
			clear_lexer_head(&data->lexer_head);
		rl_clear_history();
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
		free_reset_ptr(env_head->name);
		free_reset_ptr(env_head->infos);
		free_reset_ptr(env_head);
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
		free_reset_ptr(env_arr[index]);
		env_arr[index] = NULL;
		index++;
	}
	free_reset_ptr(env_arr);
	return ;
}

void	clear_lexer_head(t_lexer **lexer_head)
{
	t_lexer	*tmp;

	tmp = NULL;
	while (*lexer_head)
	{
		tmp = (*lexer_head)->next;
		if ((*lexer_head)->token == WORD)
			free((*lexer_head)->word);
		free(*lexer_head);
		*lexer_head = tmp;
	}
}
