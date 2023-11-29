/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:31:38 by fbesson           #+#    #+#             */
/*   Updated: 2023/11/29 17:56:30 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_builtin builtins[] =
{
		{"echo", builtin_echo},
		{"env", builtin_env},
		{"pwd", builtin_pwd},
		{"exit", builtin_exit},
		{"unset", builtin_unset},
		{"export", builtin_export},
		{"cd", builtin_cd},
		{NULL, NULL}
};

int	execute_builtin(t_data *data, t_cmd *cmd)
{
	(void)cmd;
	int i;
	char *command_name;
	command_name = data->lexer_head->word;

	i = 0;
	while (builtins[i].name)
	{
		if (ft_strcmp(command_name, builtins[i].name) == 0)
			return (builtins[i].func(data, cmd));
		i++;
	}
	return (CMD_NOT_FOUND);
}
