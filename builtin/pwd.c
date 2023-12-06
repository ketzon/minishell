/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:05:04 by fbesson           #+#    #+#             */
/*   Updated: 2023/12/06 15:34:20 by fbesson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void mute(char **dont_need)
{
	(void)dont_need;
}

int	builtin_pwd(t_data *data, char **args)
{
		mute(args);
		char buffer[PATH_MAX];
		char *current_wd;
		
		if (data->wd != NULL)
			return (ft_putendl_fd(data->wd, STDOUT_FILENO), 0);
		current_wd = getcwd(buffer, PATH_MAX);
		if (current_wd == NULL)
			errmsg_cmd("pwd", NULL, strerror(errno), errno);
		if (current_wd != NULL)
			return (ft_putendl_fd(current_wd, STDOUT_FILENO), 0);
		return (EXIT_FAILURE);
}
