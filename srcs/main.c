/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:30:50 by fgonzale          #+#    #+#             */
/*   Updated: 2023/12/10 21:42:31 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit_code;

bool	parse_input(t_data *data)
{
	if (data->line == NULL)
		builtin_exit(data, NULL);
	add_history(data->line);
	if (token_parse(data) == 1)
		return (false);
	if (data->lexer_head->token == END)
	{
		data->overwrite_exit_code = false;
		return (false);
	}
	if (variable_check(data) == 1)
		return (false);
	variable_expander(data);
	delete_empty_var_args(&data->lexer_head);
	handle_quotes(data);
	create_commands(data);
	if (data->overwrite_exit_code == false)
		return (false);
	if (data->cmd_head == NULL)
	{
		g_exit_code = 0;
		data->overwrite_exit_code = false;
		return (false);
	}
	return (true);
}

void	reset_loop(t_data *data)
{
	if (data)
	{
		data->overwrite_exit_code = true;
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
		if (data->env_head)
		{
			free_env_struct(data->env_head);
			data->env_head = NULL;
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (init_data(&data, envp) == false)
		exit(EXIT_FAILURE);
	(void)argc;
	(void)argv;
	while (1)
	{
		signals_handling();
		data.env_head = init_env(data.env);
		data.line = readline(PROMPT);
		if (parse_input(&data) == true)
			g_exit_code = execute(&data);
		else
		{
			if (data.overwrite_exit_code == false)
				g_exit_code = g_exit_code;
			else
				g_exit_code = 1;
		}
		reset_loop(&data);
	}
	return (0);
}
