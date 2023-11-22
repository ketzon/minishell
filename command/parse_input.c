/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:32:47 by fgonzale          #+#    #+#             */
/*   Updated: 2023/11/22 22:49:25 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	open_input(t_io_data *io, char *input_name, char *og_name)
{
	//remove_old_file();
	io->infile = ft_strdup(input_name);
	//(io_infile && io_infile[0] == '\0')
//	{
		//error_msg("ambigous redirect");
		//return ;
//	}
	io->input_fd = open(io->infile, O_RDONLY);
	if (io->input_fd == -1)
		printf("Error opening infile\n"); // Changer pour errcmd.
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
