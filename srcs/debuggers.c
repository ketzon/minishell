/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debuggers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:44:30 by fgonzale          #+#    #+#             */
/*   Updated: 2023/11/27 15:45:38 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"\

void	debugger_lexer(t_data *data)
{
	t_lexer	*tmp;
	tmp =  data->lexer_head;
	printf("-----------LEXER-------------\n");
	while (tmp)
	{
		printf("%s | Token type = %s\n", tmp->word, token_word(tmp->token));
		tmp = tmp->next;
	}
	printf("-----------------------------\n");
}

void	debugger_cmds(t_data *data)
{
	t_cmd *tmp;
	int	i;

	i = 0;
	tmp = data->cmd_head;
	printf("-----------CMDS-------------\n");
	while (tmp)
	{
		printf("Command = %s\n", tmp->command);
		while (tmp->args && tmp->args[i])
			printf("Args = %s\n", tmp->args[i++]);
		if (tmp->io_struct && tmp->io_struct->infile)
			printf("infile = %s,", tmp->io_struct->infile);
		printf(" fd = %d\n", tmp->io_struct->input_fd);
		if (tmp->io_struct && tmp->io_struct->outfile)
			printf("outfile = %s,", tmp->io_struct->outfile);
		printf(" fd = %d\n", tmp->io_struct->output_fd);
		tmp = tmp->next;
	}
	printf("-----------------------------\n");
}
