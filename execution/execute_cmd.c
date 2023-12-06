/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:46:28 by fbesson           #+#    #+#             */
/*   Updated: 2023/12/06 22:21:46 by fbesson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	execute_sys_bin(t_data *data, t_cmd *cmd)
{
	if (!cmd->command || cmd->command[0] == '\0')
		return (CMD_NOT_FOUND);
	if (cmd_is_dir(cmd->command))
		return (CMD_NOT_FOUND);
	cmd->path = get_cmd_path(data, cmd->command);
	if (!cmd->path)
		return (CMD_NOT_FOUND);
	if (execve(cmd->path, cmd->args, data->env) == -1)
		errmsg_cmd("execve", NULL, strerror(errno), errno);
	return (EXIT_FAILURE);
}

static int	execute_local_bin(t_data *data, t_cmd *cmd)
{
	int	val;

	val = check_command_not_found(data, cmd);
	if (val != 0)
		return (val);
	if (execve(cmd->command, cmd->args, data->env) == -1)
		return (errmsg_cmd("execve", NULL, strerror(errno), errno));
	return (1);
}

int	execute_command(t_data *data, t_cmd *cmd)
{
	int	val;

	if (cmd->command == NULL || cmd == NULL)
		exit_shell(data, errmsg_cmd("child", NULL,
				"parsing error: no to command to execute!", EXIT_FAILURE));
	if (check_infile_outfile(cmd->io_struct) == false)
		exit_shell(data, EXIT_FAILURE);
	set_pipe_fds(data->cmd_head, cmd);
	redirect_io(cmd->io_struct);
	close_fds(data->cmd_head, false);
	if (ft_strchr(cmd->command, '/') == NULL)
	{
		val = execute_builtin(data, cmd);
		if (val != CMD_NOT_FOUND)
			exit_shell(data, val);
		val = execute_sys_bin(data, cmd);
		if (val != CMD_NOT_FOUND)
			exit_shell(data, val);
	}
	val = execute_local_bin(data, cmd);
	exit_shell(data, val);
	return (val);
}
