/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 11:52:53 by fbesson           #+#    #+#             */
/*   Updated: 2023/12/06 22:58:14 by fbesson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	builtin_unset(t_data *data, char **args)
{
	t_lexer	*current;
	int		i;
	int		j;

	j = 0;
	(void)args;
	current = data->lexer_head->next;
	while (current)
	{
		i = 0;
		while (data->env[i])
		{
			if (ft_strncmp(data->env[i], current->word, ft_strlen(current->word)) == 0
				&& data->env[i][ft_strlen(current->word)] == '=')
			{
				free(data->env[i]);
				j = i;
				while (data->env[j])
				{
					data->env[j] = data->env[j + 1];
					j++;
				}
				break ;
			}
			i++;
		}
		current = current->next;
	}
	return (0);
}
