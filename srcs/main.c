/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:30:50 by fgonzale          #+#    #+#             */
/*   Updated: 2023/09/22 15:28:24 by fbesson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool    parse_input(t_data *data)
{
    char *tmp;
    
    tmp = ft_strtrim(data->line, " ");
    free(data->line);
    data->line = tmp;
    if (data->line == NULL)
        exit(1); // PEUT ETRE CHANGER POUR EXIT BUILTIN
    if (*data->line == '\0')
        return (false);
    if (closed_quotes(data->line) == false)
        return (ft_error(2), false);
    add_history(data->line);
    lexer(data);
    if (!variable_check(data))
        return (false);
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
	t_env	*env;
	char **env_array;

	env_array = create_env_arr(envp);
	data.env = env_array;
	env = init_env(env_array);
	(void)env;
    while (1) 
	{
        signals_handling();
        data.line = readline(PROMPT);
        if (parse_input(&data) == true)
		{
			if (execute_builtin(&data) == NOT_FIND)
			{
				/* execute_external_command(data.line); */
			}
            printf("Valid input\n");
		}
        else
            printf("Invalid input\n");
        reset_loop(&data);
    }
	return (0);
}
