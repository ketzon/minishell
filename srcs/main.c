/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:30:50 by fgonzale          #+#    #+#             */
/*   Updated: 2023/11/14 23:42:52 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool    parse_input(t_data *data)
{
	if (data->line == NULL)
	{
		free_data(data); // Remplacer par exit_builtin.
		exit(0);
	}
	// Si que des espaces return 'true'.
	// Si les quotes ne sont pas closed return false.
	add_history(data->line);
	lexer(data);
	return (true);
}

void    reset_loop(t_data *data)
{
	if (data)
	{
    	if (data->line)
        	free_reset_ptr(data->line);
	}
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
			printf("Input OK\n");
        else
           printf("Input KO\n");
        reset_loop(&data);
    }
	return (0);
}
