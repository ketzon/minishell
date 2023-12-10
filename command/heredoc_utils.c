/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 19:04:45 by fgonzale          #+#    #+#             */
/*   Updated: 2023/12/10 15:57:38 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	check_expand_var_line(t_data *data, char **line)
{
	int		i;
	char	*var_value;

	i = 0;
	while ((*line)[i])
	{
		if ((*line)[i] == '$' && invalid_next_char((*line)[i + 1]) == false
			&& var_in_quotes(*line, i) == false)
		{
			var_value = find_matching_var(data, &(*line)[i], NULL);
			replace_value_heredoc(line, var_value, i);
		}
		i++;
	}
}

static bool	signal_exit(t_data *data)
{
	if (g_exit_code == 130)
	{
		data->overwrite_exit_code = false;
		return (true);
	}
	return (false);
}

static bool	check_line(t_data *data, char **line
	, t_io_data *io, bool *return_value)
{
	if (signal_exit(data) == true)
		return (false);
	if (*line == NULL)
	{
		errmsg_cmd("warning", "heredoc delimited by EOF: wanted",
			io->heredoc_eof, true);
		*return_value = true;
		return (false);
	}
	if (ft_strcmp(*line, io->heredoc_eof) == 0)
	{
		*return_value = true;
		return (false);
	}
	if (io->heredoc_quotes == false && ft_strchr(*line, '$'))
	{
		check_expand_var_line(data, line);
		if ((*line) == NULL)
		{
			free_reset_ptr(*line);
			*return_value = false;
			return (false);
		}
	}
	return (true);
}

void	sigint_hd_handle(int signal)
{
	(void)signal;
	g_exit_code = 130;
	ft_putchar('\n');
	close(STDIN_FILENO);
}

bool	fill_heredoc(t_data *data, t_io_data *io, int temp_fd)
{
	char	*line;
	bool	return_value;
	int		temp_stdin;

	return_value = false;
	line = NULL;
	g_exit_code = 0;
	temp_stdin = dup(STDIN_FILENO);
	signal(SIGINT, &sigint_hd_handle);
	while (1)
	{
		line = readline("> ");
		if (check_line(data, &line, io, &return_value) == false)
			break ;
		ft_putendl_fd(line, temp_fd);
		free_reset_ptr(line);
	}
	dup2(temp_stdin, STDIN_FILENO);
	free_reset_ptr(line);
	return (return_value);
}
