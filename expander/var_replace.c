/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_replace.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 17:53:34 by fgonzale          #+#    #+#             */
/*   Updated: 2023/12/05 21:52:33 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	delete_var_name(t_lexer *node, int index)
{
	char	*og_string;
	char	*new_string;
	int		var_name_len;
	int		new_string_len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	og_string = node->word;
	var_name_len = var_word_len(&node->word[index + 1]);
	new_string_len = ft_strlen(node->word) - var_name_len;
	new_string = malloc(sizeof(char) * new_string_len + 1);
	if (!new_string)
		return (1);
	while (og_string[i])
	{
		if (i == index && og_string[i] == '$')
		{
			i += var_name_len + 1;
			if (og_string[i] == '\0')
				break ;
		}
		new_string[j++] = og_string[i++];
	}
	new_string[j] = '\0';
	free(node->word);
	node->word = new_string;
	return (0);
}

char	*delete_var_name_and_replace(t_lexer *node, char *var_value, int index)
{
	char	*og_string;
	char	*new_string;
	int		var_name_len;
	int		new_string_len;
	int		i;
	int		j;
	int		z;

	i = 0;
	j = 0;
	z = 0;
	og_string = node->word;
	var_name_len = var_word_len(&og_string[index + 1]);
	new_string_len = ft_strlen(og_string) - var_name_len + ft_strlen(var_value);
	new_string = malloc(sizeof(char) * new_string_len + 1);
	if (!new_string)
		return (NULL);
	while (og_string[i])
	{
		if (i == index && og_string[i] == '$')
		{
			while (var_value[z])
				new_string[j++] = var_value[z++];
			i += var_name_len + 1;
			if (og_string[i] == '\0')
				break ;
		}
		new_string[j++] = og_string[i++];
	}
	new_string[j] = '\0';
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
