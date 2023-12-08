/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:30:50 by fgonzale          #+#    #+#             */
/*   Updated: 2023/12/08 20:39:45 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit_code = 0;

bool	parse_input(t_data *data)
{
	if (data->line == NULL)
		builtin_exit(data, NULL);
	add_history(data->line);
	if (token_parse(data) == 1)
		return (false);
	if (data->lexer_head->token == END)
	{
		data->overwrite_exit_code = false; // ?
		return (false);
	}
	if (variable_check(data) == 1)
		return (false);
	variable_expander(data);
	delete_empty_var_args(&data->lexer_head); // ?
	handle_quotes(data);
	create_commands(data);
	if (data->overwrite_exit_code == false) // ?
		return (false);
	if (data->cmd_head == NULL) // ?
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
		data->overwrite_exit_code = true; // ?
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

static void	init_builtins(t_data *data)
{
	data->builtins[0] = (t_builtin){"echo", &builtin_echo};
	data->builtins[1] = (t_builtin){"env", &builtin_env};
	data->builtins[2] = (t_builtin){"pwd", &builtin_pwd};
	data->builtins[3] = (t_builtin){"unset", &builtin_unset};
	data->builtins[4] = (t_builtin){"export", &builtin_export};
	data->builtins[5] = (t_builtin){"cd", &builtin_cd};
	data->builtins[6] = (t_builtin){"exit", &builtin_exit};
	data->builtins[7] = (t_builtin){NULL, NULL};
}

static bool	init_data(t_data *data, char **envp)
{
	data->env = create_env_arr(envp);
	data->env_head = init_env(data->env);
	if (init_wds(data) == false)
	{
		errmsg_cmd("Fatal", NULL, "Could not initialize working directories", 1);
		return (false);
	}
	init_builtins(data);
	data->line = NULL;
	data->lexer_head = NULL;
	data->cmd_head = NULL;
	data->pid = -1;
	data->overwrite_exit_code = true; // ?
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
