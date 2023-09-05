/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:30:50 by fgonzale          #+#    #+#             */
/*   Updated: 2023/09/05 11:13:52 by fbesson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
    char    *env_path;
    char    *line;
    (void)argc;
    (void)argv;
    
    env_path = get_env_path(envp);
	(void)env_path;
    while (1)
    {
        signals_handling();
        line = readline("$minishell : ");
        if (line == NULL) // READLINE RENVOI NULL DANS LE CAS DE CTRL + D , PERMET DE QUITTER PROPREMENT.
            break ;
        if (!*(line + ft_skip_white_spaces(line)))
        {
            free(line);
            continue ;
        }
		if (!count_quotes(line)) //check si les parentheses match
			return (free(line), ft_error(2));//si les quotes match pas, return error sortie 2 et print msg
        add_history(line);
        free(line);
    }
}
