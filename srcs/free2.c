/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 16:54:26 by fgonzale          #+#    #+#             */
/*   Updated: 2023/12/09 16:57:12 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	close_fds(t_cmd *cmds, bool close_backups)
{
	if (cmds->io_struct)
	{
		if (cmds->io_struct->input_fd != -1)
			close(cmds->io_struct->input_fd);
		if (cmds->io_struct->output_fd != -1)
			close(cmds->io_struct->output_fd);
		if (close_backups)
			restore_io(cmds->io_struct);
	}
	close_pipe_fds(cmds, NULL);
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
