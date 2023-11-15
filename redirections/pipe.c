/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbesson <fbesson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 18:53:52 by fbesson           #+#    #+#             */
/*   Updated: 2023/11/15 13:47:38 by fbesson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	create_pipes(t_data *data)
{
	int *fd;	
	t_command *cmd;

	cmd = data->cmd;
	while (cmd)
	{
		if (cmd->pipe_output || (cmd->prev && cmd->prev->pipe_output))
		{
			fd = malloc(sizeof(int) * 2);
			if (!fd || pipe(fd) != 0)
			{
				free_data(data, false);
				return (false);
			}
			cmd->pipe_fd = fd;
		}
		cmd = cmd->next;
	}
	return (true);
}


