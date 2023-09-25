/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbesson <fbesson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:04:15 by fbesson           #+#    #+#             */
/*   Updated: 2023/09/20 12:04:39 by fbesson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	builtin_env(t_data *data)
{
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
