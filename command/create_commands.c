/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 17:31:28 by fbesson           #+#    #+#             */
/*   Updated: 2023/09/28 22:40:04 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_cmd	*cmd_new_node()
{
	t_cmd *new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return NULL;
	new->cmd = NULL;
	new->args = NULL;
	new->previous = NULL;
	new->next = NULL;
	return (new);
}

static void	cmd_add_bottom(t_cmd **cmd_head, t_cmd *new_node)
{
	t_cmd	*cmd_head_tmp;

	cmd_head_tmp = *cmd_head;
	if (*cmd_head == NULL)
	{
		*cmd_head = new_node;
		return ;
	}
	while (cmd_head_tmp && cmd_head_tmp->next)
		cmd_head_tmp = cmd_head_tmp->next;
	cmd_head_tmp->next = new_node;
	new_node->previous = cmd_head_tmp;
}

static t_cmd	*get_bottom_cmd(t_cmd **cmd_head)
{
	t_cmd	*temp;

	temp = *cmd_head;
	while(temp && temp->next)
		temp = temp->next;
	return(temp);
}

static void	fill_word(t_cmd **cmd_head,  t_lexer **node)
{
	t_lexer	*node_temp;
	t_cmd	*bottom_cmd;

	node_temp = *node;
	while (node_temp && (node_temp->token == WORD || node_temp->token == VAR))
	{
		bottom_cmd = get_bottom_cmd(cmd_head);
		if (node_temp->previous == NULL || bottom_cmd->cmd == NULL)
		{
			bottom_cmd->cmd = ft_strdup(node_temp->word);
			node_temp = node_temp->next;
		}
		else
			//fill_args;
	}
	*node = node_temp;
}

void	create_commands(t_data *data)
{
	t_lexer *tmp;
	t_cmd	*cmd_head;
	bool	init_list;

	init_list = true;
	tmp = data->lexer_head;
	while (tmp)
	{
		if (init_list == true)
		{
			cmd_add_bottom(&cmd_head, cmd_new_node());
			init_list = false;
		}
		if (tmp->token == WORD || tmp->token == VAR)
			fill_word(&cmd_head, &tmp);
	}
	printf("%s\n", cmd_head->cmd);
}