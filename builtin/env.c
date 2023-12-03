/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:04:15 by fbesson           #+#    #+#             */
/*   Updated: 2023/12/03 16:00:49 by fbesson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	builtin_env(t_data *data, char **args)
{
		(void)args;
		int i;
		char **env_vars;

		env_vars = data->env;
		i = 0;
		while (env_vars && env_vars[i])
		{
				printf("%s\n", env_vars[i]);
				i++;
		}
		return (0);
}
