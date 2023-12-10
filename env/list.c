/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 16:45:12 by fbesson           #+#    #+#             */
/*   Updated: 2023/12/08 21:06:45 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*extract_content(char *line, int start, int end)
{
	int		index;
	int		len;
	char	*content;

	index = 0;
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
	int		index;
	int		start;
	int		end;
	char	*name;

	start = 0;
	index = 0;
	end = 0;
	if (!line)
		return (NULL);
	while (line[index] != 0)
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

char	*get_line_infos(char *line)
{
	int		index;
	int		start;
	int		end;
	char	*infos;

	if (!line)
		return (NULL);
	index = 0;
	while (line[index])
	{
		if (line[index] == '=' && !(ws(line[index + 1])))
		{
			start = ++index;
			end = ft_strlen(line);
			infos = extract_content(line, start, end);
			if (is_value_null(infos))
				return (free(infos), NULL);
			return (infos);
		}
		index++;
	}
	return (NULL);
}

void	create_env_list(t_var **env_head, char **env_arr)
{
	int		index;
	int		id;
	char	*name;
	char	*infos;
	t_var	*list;

	id = 1;
	index = 0;
	while (env_arr[index] != NULL)
	{
		name = get_line_name(env_arr[index]);
		infos = get_line_infos(env_arr[index]);
		list = init_env_var(name, infos, id);
		create_list(env_head, list);
		index++;
	}
}
