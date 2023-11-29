/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:06:29 by fbesson           #+#    #+#             */
/*   Updated: 2023/11/29 18:11:02 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	builtin_echo(t_data *data, t_cmd *cmd)
{
	(void)cmd;
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
