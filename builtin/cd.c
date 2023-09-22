/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbesson <fbesson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 11:52:33 by fbesson           #+#    #+#             */
/*   Updated: 2023/09/22 16:37:36 by fbesson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	builtin_cd(t_data *data)
{
	char *path;
	t_lexer *current;

	current = data->lexer_head->next;
	if (current == NULL) 
	{
		path = data->env_head->home_path;
		if (path == NULL)
		{
			printf("cd: HOME environment variable not set\n");
			return (1);
		}
	} 
	else 
	{
		path = current->word;
	}
	if (chdir(path) != 0) 
	{
		printf("cd: %s: %s\n", path, strerror(errno));
		return (1);
	}
	return (0);
}
