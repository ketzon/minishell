/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:37:39 by fbesson           #+#    #+#             */
/*   Updated: 2023/12/07 23:06:01 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_reset_ptr(void	*ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}

void	free_data(t_data *data, bool clear_history)
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
		if (data->cmd_head)
			clear_cmd_head(&data->cmd_head);
		if (clear_history == true)
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
	int	index;

	index = 0;
	if (env_arr == NULL)
		return ;
	while (env_arr[index] != NULL)
	{
		if (env_arr[index])
		{
			free_reset_ptr(env_arr[index]);
			env_arr[index] = NULL;
		}
		index++;
	}
	free_reset_ptr(env_arr);
	env_arr = NULL;
	return ;
}

void	free_strs(char **strs)
{
	int	i;

	i = 0;
	if (!strs)
		return ;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

void	clear_lexer_head(t_lexer **lexer_head)
{
	t_lexer	*tmp;

	tmp = NULL;
	while (*lexer_head)
	{
		tmp = (*lexer_head)->next;
		if ((*lexer_head)->token == WORD || (*lexer_head)->token == VAR)
			free((*lexer_head)->word);
		if ((*lexer_head)->word_backup)
			free((*lexer_head)->word_backup);
		free(*lexer_head);
		*lexer_head = tmp;
	}
}

void	clear_cmd_head(t_cmd **cmd_head)
{
	t_cmd	*temp;

	temp = NULL;
	while (*cmd_head != NULL)
	{
		temp = (*cmd_head)->next;
		if ((*cmd_head)->command)
		{
			free_reset_ptr((*cmd_head)->command);
			(*cmd_head)->command = NULL;
		}
		if ((*cmd_head)->args)
		{
			free_str_tab((*cmd_head)->args);
			(*cmd_head)->args = NULL;
		}
		if ((*cmd_head)->pipe_fd)
		{
			free((*cmd_head)->pipe_fd);
			(*cmd_head)->pipe_fd = NULL;
		}
		if ((*cmd_head)->io_struct)
		{
			free_io_struct((*cmd_head)->io_struct);
			(*cmd_head)->io_struct = NULL;
		}
		free(*cmd_head);
		*cmd_head = temp;
	}
}

void	free_io_struct(t_io_data *io)
{
	if (io == NULL)
		return ;
	restore_io(io);
	if (io->heredoc_eof)
	{
		unlink(io->infile);
		free(io->heredoc_eof);
	}
	if (io->infile)
		free(io->infile);
	if (io->outfile)
		free(io->outfile);
	if (io)
		free(io);
}
