/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:30:50 by fgonzale          #+#    #+#             */
/*   Updated: 2023/12/07 00:08:42 by fgonzale         ###   ########.fr       */
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
	//delete_empty_var_args(&data->lexer_head);
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

static bool	init_wds(t_data *data)
{
	char	buff[PATH_MAX];
	char	*wd;

	wd = getcwd(buff, PATH_MAX);
	data->wd = ft_strdup(wd);
	if (data->wd == NULL)
		return (false);
	if (is_index(data->env, "OLDPWD") != -1)
		data->old_wd = get_line_infos("OLDPWD");
	else
	{
		data->old_wd = ft_strdup(wd);
		if (data->old_wd == NULL)
			return (false);
	}
	return (true);
}

static bool	init_data(t_data *data, char **envp)
{
	data->builtins =
	{
		{"echo", builtin_echo},
		{"env", builtin_env},
		{"pwd", builtin_pwd},
		{"exit", builtin_exit},
		{"unset", builtin_unset},
		{"export", builtin_export},
		{"cd", builtin_cd},
		{NULL, NULL}
	};
	data->env = create_env_arr(envp);
	data->env_head = init_env(data->env);
	if (init_wds(data) == false)
	{
		errmsg_cmd("Fatal", NULL, "Could not initialize working directories", 1);
		return (false);
	}
	data->line = NULL;
	data->lexer_head = NULL;
	data->cmd_head = NULL;
	data->pid = -1;
	return (true);
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
