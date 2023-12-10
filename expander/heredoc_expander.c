/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expander.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 03:49:05 by fgonzale          #+#    #+#             */
/*   Updated: 2023/12/10 18:53:05 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*malloc_new_string_heredoc(char **line, int var_name_len,
	char *var_value)
{
	char	*new_string;
	int		new_string_len;

	if (var_value != NULL)
		new_string_len = ft_strlen(*line)
			- var_name_len + ft_strlen(var_value);
	else
		new_string_len = ft_strlen(*line) - var_name_len;
	new_string = ft_calloc(new_string_len + 1, sizeof(char));
	if (!new_string)
		return (NULL);
	return (new_string);
}

int	delete_var_name_heredoc(char **line, int index)
{
	char	*new_string;
	int		var_name_len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	var_name_len = var_word_len(&(*line)[index + 1]);
	new_string = malloc_new_string_heredoc(line, var_name_len, NULL);
	if (!new_string)
		return (1);
	while ((*line)[i])
	{
		if (i == index && (*line)[i] == '$')
		{
			i += var_name_len + 1;
			if ((*line)[i] == '\0')
				break ;
		}
		new_string[j++] = (*line)[i++];
	}
	new_string[j] = '\0';
	free(*line);
	*line = new_string;
	return (0);
}

void	write_new_string_heredoc(char **line, int index,
	char *var_value, char *new_string)
{
	int	var_name_len;
	int	i;
	int	z;
	int	j;

	j = 0;
	z = 0;
	i = 0;
	var_name_len = var_word_len(&(*line)[index + 1]);
	while ((*line)[i])
	{
		if (i == index && (*line)[i] == '$')
		{
			while (var_value[z])
				new_string[j++] = var_value[z++];
			i += var_name_len + 1;
			if ((*line)[i] == '\0')
				break ;
		}
		new_string[j++] = (*line)[i++];
	}
	new_string[j] = '\0';
}

char	*delete_var_name_and_replace_heredoc(char **line,
		char *var_value, int index)
{
	char	*new_string;
	int		var_name_len;

	var_name_len = var_word_len(&(*line)[index + 1]);
	new_string = malloc_new_string_heredoc(line, var_name_len, var_value);
	if (!new_string)
		return (NULL);
	write_new_string_heredoc(line, index, var_value, new_string);
	free(*line);
	*line = new_string;
	return (new_string);
}

int	replace_value_heredoc(char **line, char *var_value, int index)
{
	if (var_value == NULL)
	{
		if (delete_var_name_heredoc(line, index) == 1)
			return (free(var_value), 1);
	}
	else
	{
		if (delete_var_name_and_replace_heredoc(line, var_value, index) == NULL)
			return (free(var_value), 1);
	}
	return (free(var_value), 1);
}
