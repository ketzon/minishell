/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chained.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:10:12 by fbesson           #+#    #+#             */
/*   Updated: 2023/12/07 19:41:23 by fbesson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	connect_node(t_var *curr_node, t_var *next_node)
{
	curr_node->next = next_node;
	next_node->prev = curr_node;
}

void	create_list(t_var **env_head, t_var *node)
{
	t_var	*curr;
	int		index;

	index = 0;
	if (*env_head == NULL)
	{
		*env_head = node;
		node->index = index;
	}
	else
	{
		curr = *env_head;
		index++;
		while (curr->next)
		{
			index++;
			curr = curr->next;
		}
		node->index = index;
		connect_node(curr, node);
	}
}
