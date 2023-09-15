/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:30:50 by fgonzale          #+#    #+#             */
/*   Updated: 2023/09/15 15:07:03 by fbesson          ###   ########.fr       */
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
    //CHECK IF VARIABLES(data->lexer_head);
    return (true);
}

void    reset_loop(t_data *data)
{
    if (data->line)
        free(data->line);
}

int main(int , char **, char **envp)
{
    /* t_data  data; */
	t_env	*env;
	char **env_array;
    

    /* data.env_paths = get_env_path(envp); */
    /* while (1) */ 
	/* { */
    /*     signals_handling(); */
    /*     data.line = readline(PROMPT); */
    /*     if (parse_input(&data) == true) */
    /*         printf("Valid input\n"); */
    /*     else */
            /* printf("Invalid input\n"); */
        /* reset_loop(&data); */
    /* } */
	env_array = create_env_arr(envp);
	env = init_env(env_array); 
    /* data.env_paths = get_env_path(envp); */
	while (env->first_node)
	{
		printf("Name : %s\n", env->first_node->name);
		printf("Infos : %s\n", env->first_node->infos);
		printf("%s\n", "------------------------------------------------");
		env->first_node = env->first_node->next;
	}
    /* while (1) */
    /* { */
    /*     signals_handling(); */
    /*     line = readline("$minishell : "); */
    /*     if (line == NULL) */
    /*         break ; */
    /*     if (!*(line + ft_skip_white_spaces(line))) */
    /*     { */
    /*         free(line); */
    /*         continue ; */
    /*     } */
		/* if (!count_quotes(line)) */ 
			/* return (free(line), ft_error(2)); */
    /*     add_history(line); */
    /*     lexer(&data, line); */
    /*     free(line); */
	return (0);
    /* } */
}
