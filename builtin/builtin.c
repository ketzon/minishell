/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbesson <fbesson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:31:38 by fbesson           #+#    #+#             */
/*   Updated: 2023/09/20 13:47:04 by fbesson          ###   ########.fr       */
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
		/* {"export", builtin_export}, */
		{"cd", builtin_cd},
		{NULL, NULL}
};

int	execute_builtin(t_data *data)
{
	int i;
	char *command_name;
	command_name = data->lexer_head->word;

	i = 0;
	while (builtins[i].name)
	{
		if (ft_strcmp(command_name, builtins[i].name) == 0)
			return (builtins[i].func(data));
		i++;
	}
	return (NOT_FIND);
}