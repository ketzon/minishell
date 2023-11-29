/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:41:45 by fbesson           #+#    #+#             */
/*   Updated: 2023/11/29 21:47:38 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int get_children(t_data *data)
{
	pid_t wpid;
	int status;
	int save_status;

	close_fds(data->cmd_head, false);
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
	t_cmd 	*cmd;

	cmd = data->cmd_head;
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

	io_val = check_infile_outfile(data->cmd_head->io_struct);
	if (!data || !data->cmd_head)
		return (EXIT_SUCCESS);
	if (!data->cmd_head->command)
	{
		if (data->cmd_head->io_struct && !io_val)
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
	if (!data->cmd_head->pipe_output && !data->cmd_head->previous
		&& check_infile_outfile(data->cmd_head->io_struct))
	{
		redirect_io(data->cmd_head->io_struct);
		val = execute_builtin(data, data->cmd_head);
		restore_io(data->cmd_head->io_struct);
	}
	if (val != CMD_NOT_FOUND)
		return (val);
	return (create_children(data));
}
