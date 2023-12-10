/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 21:53:52 by fgonzale          #+#    #+#             */
/*   Updated: 2023/12/10 17:25:03 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	initialise_io(t_cmd *cmd_node)
{
	if (cmd_node->io_struct)
		return ;
	cmd_node->io_struct = malloc(sizeof(t_io_data));
	if (!cmd_node->io_struct)
		return ;
	cmd_node->io_struct->heredoc_eof = NULL;
	cmd_node->io_struct->infile = NULL;
	cmd_node->io_struct->outfile = NULL;
	cmd_node->io_struct->heredoc_quotes = false;
	cmd_node->io_struct->input_fd = -1;
	cmd_node->io_struct->output_fd = -1;
	cmd_node->io_struct->stdin_backup = -1;
	cmd_node->io_struct->stdout_backup = -1;
}

void	init_builtins(t_data *data)
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

bool	init_data(t_data *data, char **envp)
{
	g_exit_code = 0;
	data->env = create_env_arr(envp);
	data->env_head = init_env(data->env);
	if (init_wds(data) == false)
	{
		errmsg_cmd("Fatal", NULL,
			"Could not initialize working directories", 1);
		return (false);
	}
	free_env_struct(data->env_head);
	init_builtins(data);
	data->line = NULL;
	data->lexer_head = NULL;
	data->cmd_head = NULL;
	data->env_head = NULL;
	data->pid = -1;
	data->overwrite_exit_code = true;
	return (true);
}

bool	init_wds(t_data *data)
{
	char	buff[PATH_MAX];
	char	*wd;

	wd = getcwd(buff, PATH_MAX);
	data->wd = ft_strdup(wd);
	if (data->wd == NULL)
		return (false);
	if (is_index(data->env, "OLDPWD") != -1)
		data->old_wd = get_var_value(data, "OLDPWD");
	else
	{
		data->old_wd = ft_strdup(wd);
		if (data->old_wd == NULL)
			return (false);
	}
	return (true);
}
