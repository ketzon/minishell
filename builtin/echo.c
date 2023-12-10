/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:06:29 by fbesson           #+#    #+#             */
/*   Updated: 2023/12/10 18:02:17 by fbesson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_option(char *str)
{
	if (str == NULL)
		return (0);
	if (*str == '-')
		str++;
	else
		return (0);
	if (*str == '-')
		str++;
	if (*str)
		return (1);
	return (0);
}

static int	is_valid_option(char *str)
{
	if (!is_option(str))
		return (0);
	str++;
	while (*str)
	{
		if (*str != 'n')
			return (0);
		str++;
	}
	return (1);
}

int	builtin_echo(t_data *data, char **args)
{
	int	i;
	int	n;

	n = 0;
	i = 0;
	(void)data;
	if (is_valid_option(args[1]))
	{
		n = 1;
		i = 1;
	}
	while (args[++i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1] != NULL)
			ft_putstr_fd(" ", STDOUT_FILENO);
	}
	if (n == 0)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
