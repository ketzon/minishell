/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:36:54 by fgonzale          #+#    #+#             */
/*   Updated: 2023/11/27 16:39:17 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	parse_pipe(t_cmd **cmd_head, t_lexer **lexer_head)
{
	t_cmd	*last_cmd;

	last_cmd = get_last_cmd(*cmd_head);
	last_cmd->pipe_output = true;
	cmd_lst_addback(cmd_head, new_node_cmd(false));
	*lexer_head = (*lexer_head)->next;
}
