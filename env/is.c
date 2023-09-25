/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbesson <fbesson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 11:26:48 by fbesson           #+#    #+#             */
/*   Updated: 2023/09/13 16:22:59 by fbesson          ###   ########.fr       */
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
