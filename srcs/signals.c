/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 17:22:16 by fgonzale          #+#    #+#             */
/*   Updated: 2023/12/08 17:13:42 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sigint_process(int signal)
{
	(void)signal;
	ft_putchar('\n');
}

void	signals_handling(void)
{
	signal(SIGINT, sigint_handling);
	signal(SIGQUIT, SIG_IGN);
}

void	sigint_handling(int signal)
{
	g_exit_code = 130;
	ft_putchar('\n');
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	(void)signal;
}
