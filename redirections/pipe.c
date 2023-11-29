/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbesson <fbesson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 18:53:52 by fbesson           #+#    #+#             */
/*   Updated: 2023/11/26 17:10:09 by fbesson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void 	close_pipe_fds(t_command *cmds, t_command *skip_cmd)
{
	while (cmds)
	{
		if (cmds != skip_cmd && cmds->pipe_fd)
		{
			close(cmds->pipe_fd[0]);
			close(cmds->pipe_fd[1]);
		}
		cmds = cmds->next;
	}
}

bool 	set_pipe_fds(t_command *cmds, t_command *cmd)
{
	if (cmd == NULL)
		return (false);
	if (cmd->prev && cmd->prev->pipe_output)
		dup2(cmd->prev->pipe_fd[0], STDIN_FILENO);
	if (cmd->pipe_output)
		dup2(cmd->pipe_fd[1], STDOUT_FILENO);
	close_pipe_fds(cmds, cmd);
	return (true);
}

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


