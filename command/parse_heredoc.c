/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 15:56:18 by fgonzale          #+#    #+#             */
/*   Updated: 2023/12/05 22:29:59 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*get_heredoc_name(void)
{
	char			*tmp_name = "/tmp/.mini_heredoc_";
	static int		number;
	char			*number_char;
	char			*heredoc_name;

	number = 1;
	number_char = ft_itoa(number);
	if (!number_char)
		return (NULL);
	heredoc_name = ft_strjoin(tmp_name, number_char);
	free(number_char);
	number++;
	return (heredoc_name);
}

static char	*get_eof(char *eof, bool *quotes)
{
	int		end;
	char	*new_eof;

	end = ft_strlen(eof) - 1;
	if ((eof[0] == '\"' && eof[end] == '\"') || (eof[0] == '\'' && eof[end] == '\''))
	{
		*quotes = true;
		new_eof = ft_strtrim(eof, "\'\"");
		return (new_eof);
	}
	new_eof = ft_strdup(eof);
	return (new_eof);
}

static bool	create_heredoc(t_data *data, t_io_data *io)
{
	bool	return_value;
	int		temp_fd;

	return_value = true;
	temp_fd = open(io->infile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	return_value = fill_heredoc(data, io, temp_fd);
	close (temp_fd);
	return (return_value);
}

void	parse_heredoc(t_data *data, t_cmd **cmd_head, t_lexer **lexer_head)
{
	t_cmd	*last_cmd;

	last_cmd = get_last_cmd(*cmd_head);
	initialise_io(last_cmd);
	if (erase_previous_file(last_cmd->io_struct, true) == false)
		return ;
	last_cmd->io_struct->infile = get_heredoc_name();
	last_cmd->io_struct->heredoc_eof = get_eof((*lexer_head)->next->word, &last_cmd->io_struct->heredoc_quotes);
	if (create_heredoc(data, last_cmd->io_struct) == true)
		last_cmd->io_struct->input_fd = open(last_cmd->io_struct->infile, O_RDONLY);
	else
		last_cmd->io_struct->input_fd = -1;
	if ((*lexer_head)->next->next)
		*lexer_head = (*lexer_head)->next->next;
	else
		*lexer_head = (*lexer_head)->next;
}
