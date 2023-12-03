/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:05:04 by fbesson           #+#    #+#             */
/*   Updated: 2023/12/03 16:02:15 by fbesson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	builtin_pwd(t_data *data, char **args)
{
		(void)data;
		(void)args;
		char buffer[5000];

		if (getcwd(buffer, sizeof(buffer)) != NULL)
		{
				printf ("%s\n", buffer);
				return (0);
		}
		else
		{
				printf("%s\n", "Pwd: failed to get the current working directory");
				return (1);
		}
}
