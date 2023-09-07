/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 17:46:06 by fgonzale          #+#    #+#             */
/*   Updated: 2023/09/07 15:39:10 by fbesson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

char	**create_env_arr(char **envp, int ac, char **av)
{
	(t_unused)ac;
	(t_unused)av;
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
