/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:19:51 by fgonzale          #+#    #+#             */
/*   Updated: 2023/12/05 22:18:53 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	prep_no_args_commands(t_data *data)
{
	t_cmd	*cmd;

	if (!data || !data->cmd_head)
		return ;
	cmd = data->cmd_head;
	while (cmd && cmd->command)
	{
		if (!cmd->args)
		{
			cmd->args = malloc(sizeof(char *) * 2);
			if (!cmd->args)
				return ;
			cmd->args[0] = ft_strdup(cmd->command);
			cmd->args[1] = NULL;
		}
		cmd = cmd->next;
	}
	cmd = get_last_cmd(cmd);
}

void	create_commands(t_data *data)
{
	t_lexer	*tmp;

	tmp = data->lexer_head;
	if (tmp->token == END)
		return ;
	while (tmp->next != NULL)
	{
		if (tmp == data->lexer_head)
			cmd_lst_addback(&data->cmd_head, new_node_cmd(false));
		if (tmp->token == WORD || tmp->token == VAR)
			parse_words(&data->cmd_head, &tmp);
		else if (tmp->token == INPUT)
			parse_input_cmd(&data->cmd_head, &tmp);
		else if (tmp->token == OUTPUT)
			parse_output(&data->cmd_head, &tmp);
		else if (tmp->token == HEREDOC)
			parse_heredoc(data, &data->cmd_head, &tmp);
		else if (tmp->token == OUTAPPEND)
			parse_output_append(&data->cmd_head, &tmp);
		else if (tmp->token == PIPE)
			parse_pipe(&data->cmd_head, &tmp);
		else if (tmp->token == END)
			break ;
	}
	prep_no_args_commands(data);
}
