/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbesson <fbesson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:41:45 by fbesson           #+#    #+#             */
/*   Updated: 2023/11/14 18:53:13 by fbesson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int init_exec(t_data *data)
{
	int io_val;

	io_val = check_infile_outile(data->cmd->io_fds)
	if (!data || !data->cmd)
		return (0);
	if (!data->cmd->command)
	{
		if (data->cmd->io_fds && !io_val)
				return (1);
		return (0);
	}
}

int	execute(t_data *data)
{
	int ret;

	ret = init_exec(data);
}
