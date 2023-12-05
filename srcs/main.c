/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:30:50 by fgonzale          #+#    #+#             */
/*   Updated: 2023/12/05 21:28:14 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int g_exit_code = 0;

bool	parse_input(t_data *data)
{
	if (data->line == NULL)
	{
		free_data(data, true);
		exit(0);
	}
	// Verifier que la chaine n'est pas simplement vide.
	// Si que des espaces return 'true'.
	add_history(data->line);
	if (token_parse(data) == 1)
		return (false);
	if (data->lexer_head->token == END)
		return (false);
	if (variable_check(data) == 1)
		return (false);
	variable_expander(data);
	handle_quotes(data);
	//debugger_lexer(data);
	create_commands(data);
	//debugger_cmds(data);
	return (true);
}

void	reset_loop(t_data *data)
{
	if (data)
	{
		if (data->line)
		{
			free_reset_ptr(data->line);
			data->line = NULL;
		}
		if (data->lexer_head)
		{
			clear_lexer_head(&data->lexer_head);
			data->lexer_head = NULL;
		}
		if (data->cmd_head)
		{
			clear_cmd_head(&data->cmd_head);
			data->cmd_head = NULL;
		}
	}
}

static void	init_data(t_data *data, char **envp)
{
	data->env = create_env_arr(envp);
	data->env_head = init_env(data->env);
	data->line = NULL;
	data->lexer_head = NULL;
	data->cmd_head = NULL;
	data->pid = -1;
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argc;
	(void)argv;
	init_data(&data, envp);
	while (1)
	{
		signals_handling();
		data.line = readline(PROMPT);
		//ajouter signals_handling_noninteractive;
		if (parse_input(&data) == true)
			g_exit_code = execute(&data);
		else
			g_exit_code = 1;
		reset_loop(&data);
	}
	return (0);
}
