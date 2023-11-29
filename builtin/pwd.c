/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:05:04 by fbesson           #+#    #+#             */
/*   Updated: 2023/11/29 18:11:45 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	builtin_pwd(t_data *data, t_cmd *cmd)
{
		(void)data;
		(void)cmd;
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
