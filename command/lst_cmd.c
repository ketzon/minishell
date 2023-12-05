/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:25:49 by fgonzale          #+#    #+#             */
/*   Updated: 2023/12/05 22:29:30 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd	*get_last_cmd(t_cmd *cmd_lst)
{
	while (cmd_lst && cmd_lst->next)
		cmd_lst = cmd_lst->next;
	return (cmd_lst);
}

t_cmd	*new_node_cmd(bool value)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->pipe_output = value;
	new->args = NULL;
	new->command = NULL;
	new->path = NULL;
	new->pipe_fd = NULL;
	new->io_struct = NULL;
	new->previous = NULL;
	new->next = NULL;
	return (new);
}

void	cmd_lst_addback(t_cmd **cmd_head, t_cmd *new_node)
{
	t_cmd	*tmp;

	tmp = *cmd_head;
	if (*cmd_head == NULL)
	{
		*cmd_head = new_node;
		return ;
	}
	if (cmd_head && *cmd_head && new_node)
	{
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
		new_node->previous = tmp;
	}
}
