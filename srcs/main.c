/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:30:50 by fgonzale          #+#    #+#             */
/*   Updated: 2023/11/16 20:07:47 by fgonzale         ###   ########.fr       */
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
	debugger_lexer(data);
	return (true);
}

void    reset_loop(t_data *data)
{
	if (data)
	{
    	if (data->line)
		{
        	free_reset_ptr(data->line);
		}
		if (data->lexer_head)
			clear_lexer_head(&data->lexer_head);
	}
}

int main(int , char **, char **envp)
{
    t_data  data;

	data.env = create_env_arr(envp);
	data.env_head = init_env(data.env);
	data.lexer_head = NULL;
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
