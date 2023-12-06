/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:04:15 by fbesson           #+#    #+#             */
/*   Updated: 2023/12/06 19:24:44 by fbesson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	builtin_env(t_data *data, char **args)
{
	int index;

	index = 0;
	if (args && args[1])
		return (errmsg_cmd("env", NULL, "too many arguments", 2));
	if (data->env == NULL)
		return (1);	
	while (data->env[index])
		ft_putendl_fd(data->env[index++], STDOUT_FILENO);
	return (0);
}
