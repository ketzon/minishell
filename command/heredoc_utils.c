/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 19:04:45 by fgonzale          #+#    #+#             */
/*   Updated: 2023/12/04 20:39:04 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	check_expand_var_line(t_data *data, char **line)
{
	int	i;
	char	*var_value;

	i = 0;
	while ((*line)[i])
	{
		if ((*line)[i] == '$' && invalid_next_char((*line)[i + 1]) == false && var_in_quotes(*line, i) == false)
		{
			var_value = find_matching_var(data, &(*line)[i], NULL);
			replace_value_heredoc(line, var_value, i);
		}
		i++;
	}
}

static bool	check_line(t_data *data, char **line, t_io_data *io, bool *return_value)
{
	if (*line == NULL)
	{
		printf("Error , YOU HAVE TO EOF\n"); // Changer pour errcmd.
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

bool	fill_heredoc(t_data *data, t_io_data *io, int temp_fd)
{
	char	*line;
	bool	return_value;

	return_value = false;
	line = NULL;
	while (1)
	{
		//gere signaux dans le heredoc.
		line = readline("> ");
		if (check_line(data, &line, io, &return_value) == false)
			break ;
		ft_putendl_fd(line, temp_fd);
		free_reset_ptr(line);
	}
	free_reset_ptr(line);
	return (return_value);
}
