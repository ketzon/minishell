/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_output_append.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:20:39 by fgonzale          #+#    #+#             */
/*   Updated: 2023/12/05 22:30:23 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	open_outfile_append(t_io_data *io, char *output_name, char *og_name)
{
	if (erase_previous_file(io, false) == false)
		return ;
	io->outfile = ft_strdup(output_name);
	if (io->outfile && io->outfile[0] == '\0')
	{
		errmsg_cmd(og_name, NULL, "ambiguous redirect", false);
		return ;
	}
	io->output_fd = open(io->outfile, O_CREAT | O_APPEND | O_WRONLY, 0664);
	if (io->output_fd == -1)
		errmsg_cmd(io->outfile, NULL, strerror(errno), false);
}

void	parse_output_append(t_cmd **cmd_head, t_lexer **lexer_head)
{
	t_cmd	*last_cmd;

	last_cmd = get_last_cmd(*cmd_head);
	initialise_io(last_cmd);
	open_outfile_append(last_cmd->io_struct, (*lexer_head)->next->word, (*lexer_head)->next->word_backup);
	if ((*lexer_head)->next->next)
		*lexer_head = (*lexer_head)->next->next;
	else
		*lexer_head = (*lexer_head)->next;
}
