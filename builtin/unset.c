/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 11:52:53 by fbesson           #+#    #+#             */
/*   Updated: 2023/12/10 19:35:14 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_env_variable_match(char *env_var, char *current_word)
{
	return (ft_strncmp(env_var, current_word, ft_strlen(current_word)) == 0
		&& env_var[ft_strlen(current_word)] == '=');
}

static void	remove_env_variable(t_data *data, int index)
{
	free(data->env[index]);
	while (data->env[index])
	{
		data->env[index] = data->env[index + 1];
		index++;
	}
}

static void	disable_env_variable(t_data *data)
{
	t_lexer	*current;
	int		i;

	current = data->lexer_head->next;
	while (current)
	{
		i = 0;
		while (data->env[i])
		{
			if (is_env_variable_match(data->env[i], current->word))
			{
				remove_env_variable(data, i);
				break ;
			}
			i++;
		}
		current = current->next;
	}
}

int	builtin_unset(t_data *data, char **args)
{
	(void)args;
	disable_env_variable(data);
	return (EXIT_SUCCESS);
}
