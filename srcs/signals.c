/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 17:22:16 by fgonzale          #+#    #+#             */
/*   Updated: 2023/09/15 13:09:47 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* INTERPRETE LES DIFFERENTS SIGNAUX */
void    signals_handling(void)
{
    signal(SIGINT, sigint_handling); // GESTION DU SIGNAL CTRL + C, renvoie a la fonction signal_handling.
    signal(SIGQUIT, SIG_IGN); // GESTION DU SIGNAL CTRL + '\' , SIG_IGN lui dit d'ignorer le signal.
}

/* FONCTION QUI GERE LE SIGNAL CTRL + C*/
void sigint_handling(int signal)
{
    ft_putchar('\n');//affiche un retour a la ligne
    rl_on_new_line();//curseur deplace sur une new ligne
    rl_replace_line("", 0);//remplace la commande en cour par une chaine vide
    rl_redisplay();//affiche le prompt
    (void)signal;
}
