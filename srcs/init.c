/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbesson <fbesson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 15:55:07 by fbesson           #+#    #+#             */
/*   Updated: 2023/09/07 16:40:06 by fbesson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*init_env(char **env_array)
{
	t_env	*env;

	env = (t_env *)malloc(sizeof(t_env));
	if (env == NULL)
		return (NULL);
	env->parsing_error = 0;
	env->processing_error = 0;
	env->env_vars = NULL;
	create_env_list(env, env_array);
}
