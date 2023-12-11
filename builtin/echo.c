/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:06:29 by fbesson           #+#    #+#             */
/*   Updated: 2023/12/11 02:35:34 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_valid_option_n(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[i] == '-' && str[i + 1] != 'n')
		return (0);
	if (str[i] == '-')
		i++;
	else
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
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
	while (args && is_valid_option_n(args[i + 1]))
	{
		n = 1;
		i++;
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
