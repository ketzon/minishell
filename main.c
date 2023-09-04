/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:30:50 by fgonzale          #+#    #+#             */
/*   Updated: 2023/09/04 16:14:48 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *get_env_path(char **envp)
{
    if (!envp || !*envp)
        return (NULL);
    while (*envp)
    {
        if (ft_strncmp(*envp, "PATH", 4) == 0)
            return (*envp + 5);
        envp++;
    }
    return (NULL);
}

int ft_skip_white_spaces(char *str)
{
    int i;

    i = 0;
    while (str[i] && str[i] == ' ')
        i++;
    return (i);
}

void sigint_handling(int signal)
{
    ft_putchar('\n');
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
    (void)signal;
}

int main(int argc, char **argv, char **envp)
{
    char    *env_path;
    char    *input;
    (void)argc;
    (void)argv;
    
    env_path = get_env_path(envp);
    (void)env_path;
    while (1)
    {
        signal(SIGINT, sigint_handling);
        input = readline("$minishell : ");
        if (!*(input + ft_skip_white_spaces(input)))
            continue;
        add_history(input);
        
        //printf("%s\n", input);
        //if (!input || !is_line_empty(input))
        //    continue;
        //printf("Input ok\n");
        
    }
}