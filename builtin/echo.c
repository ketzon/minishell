/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbesson <fbesson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:06:29 by fbesson           #+#    #+#             */
/*   Updated: 2023/09/22 12:55:31 by fbesson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	builtin_echo(t_data *data)
{
	t_lexer *current;
	current = data->lexer_head->next;

	while (current)
	{
		ft_putstr(current->word);
		if (current->next)
			ft_putchar(' ');
		current = current->next;
	}
	ft_putchar('\n');
	return (0);
}
