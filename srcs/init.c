/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 21:53:52 by fgonzale          #+#    #+#             */
/*   Updated: 2023/11/22 22:08:28 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	initialise_io(t_cmd *cmd_node)
{
	cmd_node->io_struct = malloc(sizeof(t_io_data));
	if (!cmd_node->io_struct)
		return ;
	cmd_node->io_struct->heredoc_eof = NULL;
	cmd_node->io_struct->infile = NULL;
	cmd_node->io_struct->outfile = NULL;
	cmd_node->io_struct->heredoc_quotes = false;
	cmd_node->io_struct->input_fd = -1;
	cmd_node->io_struct->output_fd = -1;
	cmd_node->io_struct->stdin_backup = -1;
	cmd_node->io_struct->stdout_backup = -1;
}
