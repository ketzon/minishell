/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 17:46:06 by fgonzale          #+#    #+#             */
/*   Updated: 2023/09/04 17:57:59 by fbesson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/* PERMET DE RECUPERER LA VARIABLE PATH DEPUIS LE POINTER ENV */
char    *get_env_path(char **envp)
{
    if (!envp || !*envp)//si env est vide
        return (NULL);
    while (*envp)//parcour le pointeur env dans le but de trouver le path
    {
        if (ft_strncmp(*envp, "PATH", 4) == 0)
            return (*envp + 5);
        envp++;
    }
    return (NULL);//si pas de path return NULL
}
