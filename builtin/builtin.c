/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:31:38 by fbesson           #+#    #+#             */
/*   Updated: 2023/12/07 22:20:14 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	execute_builtin(t_data *data, t_cmd *cmd)
{
	int		i;
	char	*command_name;

	command_name = cmd->command;
	i = 0;
	while (data->builtins[i].name)
	{
		if (ft_strcmp(command_name, data->builtins[i].name) == 0)
			return (data->builtins[i].func(data, cmd->args));
		i++;
	}
	return (CMD_NOT_FOUND);
}
