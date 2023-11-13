/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:30:50 by fgonzale          #+#    #+#             */
/*   Updated: 2023/11/13 21:35:16 by fgonzale         ###   ########.fr       */
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
