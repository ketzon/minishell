/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 18:53:52 by fbesson           #+#    #+#             */
/*   Updated: 2023/11/29 18:02:02 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void 	close_pipe_fds(t_cmd *cmds, t_cmd *skip_cmd)
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

bool 	set_pipe_fds(t_cmd *cmds, t_cmd *cmd)
{
	if (cmd == NULL)
		return (false);
	if (cmd->previous && cmd->previous->pipe_output)
		dup2(cmd->previous->pipe_fd[0], STDIN_FILENO);
	if (cmd->pipe_output)
		dup2(cmd->pipe_fd[1], STDOUT_FILENO);
	close_pipe_fds(cmds, cmd);
	return (true);
}

bool	create_pipes(t_data *data)
{
	int *fd;
	t_cmd *cmd;

	cmd = data->cmd_head;
	while (cmd)
	{
		if (cmd->pipe_output || (cmd->previous && cmd->previous->pipe_output))
		{
			fd = malloc(sizeof(int) * 2);
			if (!fd || pipe(fd) != 0)
			{
				free_data(data, false); //penser a free cmd_head.
				return (false);
			}
			cmd->pipe_fd = fd;
		}
		cmd = cmd->next;
	}
	return (true);
}


