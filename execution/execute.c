/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbesson <fbesson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:41:45 by fbesson           #+#    #+#             */
/*   Updated: 2023/11/27 10:40:29 by fbesson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int get_children(t_data *data)
{
	pid_t wpid;
	int status;
	int save_status;

	close_fds(data->cmd, false);
	save_status = 0;
	wpid = 0;
	while (wpid != -1 || errno != ECHILD)
	{
		wpid = waitpid(-1, &status, 0);
		if (wpid == data->pid)
			save_status = status;
		continue ;
	}
	if (WIFSIGNALED(save_status))
		status = 128 + WTERMSIG(save_status);
	else if (WIFEXITED(save_status))
		status = WEXITSTATUS(save_status);
	else
		status = save_status;
	return (status);
}

static int create_children(t_data *data)
{
	t_command 	*cmd;

	cmd = data->cmd;
	while (cmd != NULL && data->pid != 0)
	{
		data->pid = fork();
		if (data->pid == -1)
			return (errmsg_cmd("fork", NULL, strerror(errno), EXIT_FAILURE));
		else if (data->pid == 0)
			execute_command(data, cmd);
		cmd = cmd->next;
	}
	return (get_children(data));
}

static int init_exec(t_data *data)
{
	int io_val;

	io_val = check_infile_outfile(data->cmd->io_fds);
	if (!data || !data->cmd)
		return (EXIT_SUCCESS);
	if (!data->cmd->command)
	{
		if (data->cmd->io_fds && !io_val)
				return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	if (!create_pipes(data))
			return (EXIT_FAILURE);
	return (CMD_NOT_FOUND);
}

int	execute(t_data *data)
{
	int val;

	val = init_exec(data);
	if  (val != CMD_NOT_FOUND)
		return (val);
	if (!data->cmd->pipe_output && !data->cmd->prev
		&& check_infile_outfile(data->cmd->io_fds))
	{
		redirect_io(data->cmd->io_fds);
		val = execute_builtin(data, data->cmd);
		restore_io(data->cmd->io_fds);
	}
	if (val != CMD_NOT_FOUND)
		return (val);
	return (create_children(data));
}
