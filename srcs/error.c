/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:40:40 by fbesson           #+#    #+#             */
/*   Updated: 2023/12/11 01:17:13 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_shell(t_data *data, int exit_number)
{
	if (data)
	{
		if (data->cmd_head && data->cmd_head->io_struct)
			close_fds(data->cmd_head, true);
		free_data(data, true);
	}
	exit (exit_number);
}

int	ft_error(int error)
{
	ft_putstr_fd("minishell: ", 2);
	if (error == 2)
		ft_putstr_fd("syntax error: unexpected end of file\n", 2);
	return (0);
}

int	errmsg_cmd(char *command, char *detail,
	char *error_message, int error_nb)
{
	char	*msg;
	bool	detail_quotes;

	detail_quotes = add_detail_quotes(command);
	msg = ft_strdup("minishell: ");
	if (command != NULL)
	{
		msg = join_strs(msg, command);
		msg = join_strs(msg, ": ");
	}
	if (detail != NULL)
	{
		if (detail_quotes)
			msg = join_strs(msg, "`");
		msg = join_strs(msg, detail);
		if (detail_quotes)
			msg = join_strs(msg, "'");
		msg = join_strs(msg, ": ");
	}
	msg = join_strs(msg, error_message);
	msg = join_strs(msg, "\n");
	write(STDERR_FILENO, msg, ft_strlen(msg));
	free_ptr(msg);
	return (error_nb);
}

void	errmsg(char *errmsg, char *detail, int quotes)
{
	char	*msg;

	msg = ft_strdup("minishell: ");
	msg = join_strs(msg, errmsg);
	if (quotes)
		msg = join_strs(msg, " `");
	else
		msg = join_strs(msg, ": ");
	msg = join_strs(msg, detail);
	if (quotes)
		msg = join_strs(msg, "'");
	ft_putendl_fd(msg, STDERR_FILENO);
	free_ptr(msg);
}
