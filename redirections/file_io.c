/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_io.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 18:40:21 by fbesson           #+#    #+#             */
/*   Updated: 2023/11/29 22:13:16 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool 	restore_io(t_io_data *io)
{
	int val;

	if (io == NULL)
		return (true);
	if (io->stdin_backup != -1)
	{
		if (dup2(io->stdin_backup, STDIN_FILENO) == -1)
			val = false;
		close(io->stdin_backup);
		io->stdin_backup = -1;
	}
	if (io->stdout_backup != -1)
	{
		if (dup2(io->stdin_backup, STDIN_FILENO) == -1)
			val = false;
		close(io->stdout_backup);
		io->stdout_backup = -1;
	}
	return (val);
}
bool	redirect_io(t_io_data *io)
{
	int val;

	val = true;
	if (!io)
		return (val);
	io->stdin_backup = dup(STDIN_FILENO);
	io->stdout_backup = dup(STDOUT_FILENO);
	if (io->stdin_backup == -1)
		val = errmsg_cmd("dup", "stdin_backup", strerror(errno), false);
	if (io->stdout_backup == -1)
		val = errmsg_cmd("dup", "stdout_backup", strerror(errno), false);
	if (io->input_fd != -1)
		if (dup2(io->input_fd, STDIN_FILENO) == -1)
		val = errmsg_cmd("dup2", io->infile, strerror(errno), false);
	if (io->output_fd != -1)
	{
		if (dup2(io->output_fd, STDOUT_FILENO) == -1)
		val = errmsg_cmd("dup2", io->outfile, strerror(errno), false);
	}
	return (val);
}
bool	check_infile_outfile(t_io_data *io)
{
	if (!io)
		return (true);
	if (!io->infile && !io->outfile)
		return (true);
	if (io->infile && io->input_fd == -1)
		return (false);
	if (io->outfile && io->output_fd == -1)
		return (false);
	return (true);
}
