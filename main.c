/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:30:50 by fgonzale          #+#    #+#             */
/*   Updated: 2023/09/04 17:11:39 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* PERMET DE RECUPERER LA VARIABLE PATH DEPUIS L'ENVP */
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

/* SAUTE LES ESPACES DANS UNE STRING ET RENVOIE DE COMBIEN IL A AVANCE */
int ft_skip_white_spaces(char *str)
{
    int i;

    i = 0;
    while (str[i] && str[i] == ' ')
        i++;
    return (i);
}

/* FONCTION QUI GERE LE SIGNAL CTRL + C*/
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
        signal(SIGINT, sigint_handling); // GESTION DU SIGNAL CTRL + C, renvoie a la fonction signal_handling.
        signal(SIGQUIT, SIG_IGN); // GESTION DU SIGNAL CTRL + '\' , SIG_IGN lui dit d'ignorer le signal.
        input = readline("$minishell : ");
        if (input == NULL) // READLINE RENVOI NULL DANS LE CAS DE CTRL + D , PERMET DE QUITTER PROPREMENT.
            break;
        if (!*(input + ft_skip_white_spaces(input)))
            continue;
        add_history(input);
        
    }
}