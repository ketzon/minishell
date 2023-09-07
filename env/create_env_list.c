/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbesson <fbesson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 16:45:12 by fbesson           #+#    #+#             */
/*   Updated: 2023/09/07 17:57:39 by fbesson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell"

char	*extract_content(char *line, int start, int end)
{
	int	index;	
	char	*content;
	len = end - start + 1;
	content = malloc(sizeof(char) * (len + 1));
	while (index < len)
	{
		content[index] = line[start + index];
		index++;
	}
	content[index] = '\0';
	return (content);
}
char	*get_line_name(char *line)
{
	int	index;
	int	start;
	int	end;
	char *name;
	start = 0;
	end = 0;
	if (!line)
		return (NULL);
	while (line[index] != '\0')
	{
		if (line[index] == '=')
		{
			end = --index;
			name = extract_content(line, start, end);
			return (name);
		}
		index++;
	}
	end = index;
	name = extract_content(line, start, end);
	return (name);
}

void	create_list(t_env *env, char **env_arr);
{
	int	index;
	char	*name;
	while (env_arr[index] != NULL)
	{
		name = get_line_name(env_arr[index]);
	}
}
