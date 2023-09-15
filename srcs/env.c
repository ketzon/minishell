/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 17:46:06 by fgonzale          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/09/15 12:49:23 by fgonzale         ###   ########.fr       */
=======
<<<<<<<< HEAD:env/malloc_env.c
<<<<<<<< HEAD:env/malloc_env.c
/*   Updated: 2023/09/07 15:39:10 by fbesson          ###   ########.fr       */
========
/*   Updated: 2023/09/15 10:32:08 by fbesson          ###   ########.fr       */
>>>>>>>> env:srcs/env.c
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
========
/*   Updated: 2023/09/05 17:03:20 by fbesson          ###   ########.fr       */
>>>>>>> env
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
<<<<<<< HEAD
=======
>>>>>>>> 5684930f30fb02b89ff62a932172219cabebd101:srcs/env.c
>>>>>>> env

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
<<<<<<< HEAD
=======

int	line_count(char **envp)
{
	int	len;

	len = 0;
	while (envp[len])
		len++;
	return (len);
}

char	*malloc_each_line(char *line)
{
	int	index;
	char *line_malloc;

	index = 0;
	line_malloc = malloc(sizeof(char) * (ft_strlen(line) + 1));
	while (line[index] != '\0')
	{
		line_malloc[index] = line[index];
		index++;
	}
	line_malloc[index] = '\0';
	return (line_malloc);
}

char	**create_env_arr(char **envp)
{
	int len;
	int	index;
	char **arr;

	index = 0;
	len = line_count(envp);
	arr = malloc(sizeof(char *) * (len + 1));
	while (envp[index])
	{
		arr[index] = malloc_each_line(envp[index]);
		index++;
	}
	arr[index] = '\0';
	return (arr);
}
>>>>>>> env
