/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_replace.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 17:53:34 by fgonzale          #+#    #+#             */
/*   Updated: 2023/12/07 20:32:24 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*malloc_new_string(t_lexer *node, int var_name_len, char *var_value)
{
	char	*new_string;
	int		new_string_len;

	if (var_value != NULL)
		new_string_len = ft_strlen(node->word)
			- var_name_len + ft_strlen(var_value);
	else
		new_string_len = ft_strlen(node->word) - var_name_len;
	new_string = malloc(sizeof(char) * new_string_len + 1);
	return (new_string);
}

int	delete_var_name(t_lexer *node, int index)
{
	char	*new_string;
	int		var_name_len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	var_name_len = var_word_len(&node->word[index + 1]);
	new_string = malloc_new_string(node, var_name_len, NULL);
	if (!new_string)
		return (1);
	while (node->word[i])
	{
		if (i == index && node->word[i] == '$')
		{
			i += var_name_len + 1;
			if (node->word[i] == '\0')
				break ;
		}
		new_string[j++] = node->word[i++];
	}
	new_string[j] = '\0';
	free(node->word);
	node->word = new_string;
	return (0);
}

void	write_new_string(t_lexer *node, int index,
	char *var_value, char *new_string)
{
	int	var_name_len;
	int	i;
	int	z;
	int	j;

	j = 0;
	z = 0;
	i = 0;
	var_name_len = var_word_len(&node->word[index + 1]);
	while (node->word[i])
	{
		if (i == index && node->word[i] == '$')
		{
			while (var_value[z])
				new_string[j++] = var_value[z++];
			i += var_name_len + 1;
			if (node->word[i] == '\0')
				break ;
		}
		new_string[j++] = node->word[i++];
	}
	new_string[j] = '\0';
}

char	*delete_var_name_and_replace(t_lexer *node, char *var_value, int index)
{
	char	*new_string;
	int		var_name_len;

	var_name_len = var_word_len(&node->word[index + 1]);
	new_string = malloc_new_string(node, var_name_len, var_value);
	if (!new_string)
		return (NULL);
	write_new_string(node, index, var_value, new_string);
	free(node->word);
	node->word = new_string;
	return (new_string);
}

int	replace_value(t_lexer *node, char *var_value, int index)
{
	if (var_value == NULL)
	{
		if (delete_var_name(node, index) == 1)
			return (free(var_value), 1);
	}
	else
	{
		if (delete_var_name_and_replace(node, var_value, index) == NULL)
			return (free(var_value), 1);
	}
	return (free(var_value), 1);
}
