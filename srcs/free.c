/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbesson <fbesson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:37:39 by fbesson           #+#    #+#             */
/*   Updated: 2023/09/13 12:46:40 by fbesson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env_array(char **env_arr)
{
	int index;

	index = 0;
	if (env_arr == NULL)
		return ;
	while (env_arr[index] != NULL)
	{
		free(env_arr[index]);
		env_arr[index] = NULL;
		index++;
	}
	free(env_arr);
	return ;
}
