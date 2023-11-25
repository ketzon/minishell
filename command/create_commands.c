/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:19:51 by fgonzale          #+#    #+#             */
/*   Updated: 2023/11/26 00:27:37 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		else if(tmp->token == END)
			break ;
	}
}
