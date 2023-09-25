/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 17:46:06 by fgonzale          #+#    #+#             */
/*   Updated: 2023/09/22 15:47:21 by fbesson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

char    *get_home_path(char **envp)
{
    if (!envp || !*envp)
        return (NULL);
    while (*envp)
    {
        if (ft_strncmp(*envp, "HOME", 5) == 0)
            return (*envp + 6);
        envp++;
    }
    return (NULL);
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
