/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:06:29 by fbesson           #+#    #+#             */
/*   Updated: 2023/12/03 19:19:45 by fbesson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool is_n(char *str)
{
	int i;
	bool n_flag;

	n_flag = false;
	i = 0;
	if (str[i] != '-')
		return (n_flag);
	i++;
	while (str[i] && str[i] == 'n')
		i++;
	if (str[i] == '\0')
		n_flag = true;
	return (n_flag);
}

static void echo(char **args, bool n_flag, int i)
{
	if (args[i] == NULL)
	{
		if (n_flag == false)
			ft_putchar_fd('\n', STDOUT_FILENO);
		return ;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		else if (!args[i + 1] && n_flag == false)
			ft_putchar_fd('\n', STDOUT_FILENO);
		i++;
	}
}

int	builtin_echo(t_data *data, char **args)
{
	int i;
	bool n_flag;

	(void)data;
	i = 1;
	n_flag = false;
	while (args[i] && is_n(args[i]))
	{
		n_flag = true;
		i++;
	}
	echo(args, n_flag, i);
	return (EXIT_SUCCESS);
}
