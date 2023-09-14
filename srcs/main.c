/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:30:50 by fgonzale          #+#    #+#             */
/*   Updated: 2023/09/14 12:43:07 by fbesson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* t_env	*g_env; */

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
    /* char    *line; */
	char	**env_array;
    /* t_data  data; */
	t_env	*env;
    
	env_array = create_env_arr(envp);
	env = init_env(env_array); 
	(void)env;
    /* data.env_paths = get_env_path(envp); */
	t_env *begin = env;
	while (env->first_node)
	{
		printf("%s\n Name:", env->first_node->name);
		env->first_node = env->first_node->next;
	}
	env = begin;
	while (env->first_node)
	{
			printf("%s\n Infos:", env->first_node->infos);
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
