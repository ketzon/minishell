/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 13:36:44 by fgonzale          #+#    #+#             */
/*   Updated: 2023/12/09 18:59:36 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*extract_var_from_string(char *word)
{
	int		i;
	char	*var_name;
	int		var_name_len;

	i = 0;
	while (word[i] && word[i] != '$')
		i++;
	i++;
	var_name_len = var_word_len(&word[i]);
	var_name = ft_substr(word, i, var_name_len);
	if (!var_name)
		return (NULL);
	return (var_name);
}

char	*find_matching_var(t_data *data, char *word, t_lexer *node)
{
	char	*var_extracted;
	char	*var_value;

	var_extracted = extract_var_from_string(word);
	if (var_extracted && var_exist(data, var_extracted) == true)
	{
		var_value = get_var_value(data, var_extracted);
		if (node != NULL)
			node->var_exists = true;
	}
	else if (var_extracted && var_extracted[0] == '?'
		&& var_extracted[1] == '\0')
		var_value = ft_itoa(g_exit_code);
	else
		var_value = NULL;
	free(var_extracted);
	return (var_value);
}

static void	replace_var(t_data *data, t_lexer *node)
{
	int		i;
	char	*var_value;
	int		status;

	status = DEFAULT;
	i = 0;
	while (node->word[i])
	{
		status = get_status(status, node->word[i]);
		if (node->word[i] == '$' && (status == DEFAULT || status == DQUOTE)
			&& invalid_next_char(node->word[i + 1]) == false
			&& var_in_quotes(node->word, i) == false)
		{
			var_value = find_matching_var(data, &node->word[i], node);
			replace_value(node, var_value, i);
		}
		else
			i++;
	}
}

void	variable_expander(t_data *data)
{
	t_lexer	*tmp;

	tmp = data->lexer_head;
	while (tmp)
	{
		if (tmp->token == VAR)
			replace_var(data, tmp);
		tmp = tmp->next;
	}
}
