/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:30:50 by fgonzale          #+#    #+#             */
/*   Updated: 2023/11/15 14:10:40 by fbesson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool    parse_input(t_data *data)
{
		if (data->line == NULL)
		{
				free_data(data);
				exit(0);
		}
		return (true);
}

void    reset_loop(t_data *data)
{
		if (data->line)
				free(data->line);
}

t_io_fds *create_test_io_fds() 
{
		t_io_fds *io_fds = malloc(sizeof(t_io_fds));
		if (!io_fds) 
		{
				return NULL;
		}
		io_fds->infile = "input.txt";
		io_fds->outfile = "output.txt";
		io_fds->heredoc_delimiter = NULL;
		io_fds->heredoc_quotes = false;
		io_fds->fd_in = 0;
		io_fds->fd_out = 1;
		io_fds->stdin_backup = 0;
		io_fds->stdout_backup = 1;

		return io_fds;
}

t_command *create_test_command() 
{
		t_command *cmd = malloc(sizeof(t_command));
		if (!cmd) 
		{
				return NULL;
		}
		cmd->command = "ls";
		cmd->path = "/bin/ls";
		cmd->args = malloc(2 * sizeof(char *));
		cmd->args[0] = "ls";
		cmd->args[1] = NULL;
		cmd->pipe_output = true;
		cmd->pipe_fd = NULL;
		cmd->io_fds = create_test_io_fds();
		cmd->next = NULL;
		cmd->prev = NULL;
		return cmd;
}

void print_command_info(t_command *cmd) 
{
		int i;

		i = 0;
		if (!cmd) 
		{
				printf("Command is NULL\n");
				return;
		}
		printf("Command: %s\n", cmd->command);
		printf("Path: %s\n", cmd->path);
		printf("Arguments: ");
		while (cmd->args[i] != NULL) 
	{
        printf("%s ", cmd->args[i]);
		i++;
    }
    printf("\n");
  	printf("Pipe output: ");
    if (cmd->pipe_output) 
        printf("true\n");
	else 
        printf("false\n");
}
int main(int , char **, char **envp)
{
    t_data  data;

	data.env = create_env_arr(envp);
	data.env_head = init_env(data.env);
    while (1)
	{
        signals_handling();
        data.line = readline(PROMPT);
        if (parse_input(&data) == true)
		{
			printf("Input OK\n");
			t_command *test_cmd = create_test_command();
			print_command_info(test_cmd);
			execute(data);
		}
        else
           printf("Input KO\n");
        reset_loop(&data);
    }
	return (0);
}
