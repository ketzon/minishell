/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:30:50 by fgonzale          #+#    #+#             */
/*   Updated: 2023/09/15 10:50:56 by fbesson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* t_env	*g_env; */

int main(int , char **, char **envp)
{
    /* char    *line; */
	char	**env_array;
    /* t_data  data; */
	t_env	*env;
    
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
