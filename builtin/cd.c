/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 11:52:33 by fbesson           #+#    #+#             */
/*   Updated: 2023/11/29 18:11:17 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	builtin_cd(t_data *data, t_cmd *cmd)
{
	(void)cmd;
	char *path;
	t_lexer *current;

	current = data->lexer_head->next;
	if (current == NULL)
	{
		path = get_home_path(data->env);
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
