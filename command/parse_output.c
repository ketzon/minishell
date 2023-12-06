/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 00:27:45 by fgonzale          #+#    #+#             */
/*   Updated: 2023/12/06 18:15:49 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	open_output_trunc(t_io_data *io, char *output_name, char *og_name)
{
	if (erase_previous_file(io, false) == false)
		return ;
	io->outfile = ft_strdup(output_name);
	if (io->outfile && io->outfile[0] == '\0')
	{
		errmsg_cmd(og_name, NULL, "ambiguous redirect", false);
		return ;
	}
	io->output_fd = open(io->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (io->output_fd == -1)
		errmsg_cmd(io->outfile, NULL, strerror(errno), false);
}

void	parse_output(t_cmd **cmd_head, t_lexer **lexer_head)
{
	t_cmd	*last_cmd;

	last_cmd = get_last_cmd(*cmd_head);
	initialise_io(last_cmd);
	open_output_trunc(last_cmd->io_struct, (*lexer_head)->next->word,
		(*lexer_head)->next->word_backup);
	if ((*lexer_head)->next->next)
		*lexer_head = (*lexer_head)->next->next;
	else
		*lexer_head = (*lexer_head)->next;
}
