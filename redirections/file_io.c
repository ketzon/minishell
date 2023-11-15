/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_io.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbesson <fbesson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 18:40:21 by fbesson           #+#    #+#             */
/*   Updated: 2023/11/14 18:45:08 by fbesson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define "../includes/minishell.h"

bool	check_infile_outfile(t_io_fds *io)
{
	if (!io)
		return (true);
	if (!io->infile && !io->outfile)
		return (true);
	if (io->infile && io->fd_in == -1)
		return (false);
	if (io->outfile && io->fd_out == -1)
		return (false);
	return (true);
}
