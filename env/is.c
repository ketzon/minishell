/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 11:26:48 by fbesson           #+#    #+#             */
/*   Updated: 2023/12/07 19:54:33 by fbesson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_null(char *str)
{
	if (!str)
		return (1);
	return (0);
}

int	is_value_null(char *str)
{
	if (!str[0])
		return (1);
	return (0);
}

bool	is_valid_var_key(char *var)
{
	int	i;

	i = 0;
	if (ft_isalpha(var[i]) == 0 && var[i] != '_')
		return (false);
	i++;
	while (var[i] && var[i] != '=')
	{
		if (ft_isalnum(var[i]) == 0 && var[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

bool	is_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			return (true);
		if (str[i] == '\"')
			return (true);
		i++;
	}
	return (false);
}

int	is_index(char **env, char *var)
{
	int		index;
	char	*tmp;

	index = 0;
	tmp = ft_strjoin(var, "=");
	if (!tmp)
		return (-1);
	while (env[index])
	{
		if (ft_strncmp(tmp, env[index], ft_strlen(tmp)) == 0)
		{
			free_ptr(tmp);
			return (index);
		}
		index++;
	}
	free_ptr(tmp);
	return (-1);
}
