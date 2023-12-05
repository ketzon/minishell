/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:32:47 by fgonzale          #+#    #+#             */
/*   Updated: 2023/12/05 04:07:44 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	erase_previous_file(t_io_data *io, bool infile)
{
	if (infile == true && io->infile)
	{
		if (io->input_fd == -1 || (io->outfile && io->output_fd == -1))
			return (false);
		if (io->heredoc_eof != NULL)
		{
			free_reset_ptr(io->heredoc_eof);
			io->heredoc_eof = NULL;
			unlink(io->infile);
		}
		free(io->infile);
		close(io->input_fd);
	}
	else if (infile == false && io->outfile)
	{
		if (io->output_fd == -1 || (io->infile && io->input_fd == -1))
			return (false);
		free(io->outfile);
		close(io->output_fd);
	}
	return (true);
}

void	open_input(t_io_data *io, char *input_name, char *og_name)
{
	if (erase_previous_file(io, true) == false)
		return ;
	io->infile = ft_strdup(input_name);
	if (io->infile && io->infile[0] == '\0')
	{
		errmsg_cmd(og_name, NULL, "ambiguous redirect", false); // Changer pour errcmd.
		return ;
	}
	io->input_fd = open(io->infile, O_RDONLY);
	if (io->input_fd == -1)
		errmsg_cmd(io->infile, NULL, strerror(errno), false); // Changer pour errcmd.
}

void	parse_input_cmd(t_cmd **cmd_head, t_lexer **lexer_head)
{
	t_cmd	*last_cmd;

	last_cmd = get_last_cmd(*cmd_head);
	initialise_io(last_cmd);
	open_input(last_cmd->io_struct, (*lexer_head)->next->word, (*lexer_head)->next->word_backup);
	if ((*lexer_head)->next->next)
		*lexer_head = (*lexer_head)->next->next;
	else
		*lexer_head = (*lexer_head)->next;
}
