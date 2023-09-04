/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 17:46:06 by fgonzale          #+#    #+#             */
/*   Updated: 2023/09/04 17:46:21 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

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