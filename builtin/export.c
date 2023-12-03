/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:12:48 by fbesson           #+#    #+#             */
/*   Updated: 2023/12/03 16:05:23 by fbesson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_strncpy(char *src, char *dest, int size)
{
	int i;

	i = 0;
	if (size == 0)
	{
		printf ("%s\n", "export: No key detected");
		exit (2);
	}
	while (i < size)
	{
		src[i] = dest[i];
		i++;
	}
	return ;
}

void split_key_value(char *str, char **key, char **value)
{
    int i;

	i = 0;
    while (str[i] && str[i] != '=')
        i++;
    *key = malloc(i + 1);
    if (!(*key))
        exit(1);
    ft_strncpy(*key, str, i);
    (*key)[i] = '\0';
    if (str[i] == '=')
    {
        *value = ft_strdup(str + i + 1);
        if (!(*value))
            exit(1);
    }
    else
    {
        *value = NULL;
    }
}

void update_env_var(t_data *data, char *key, char *value, int index)
{
    int len = strlen(key) + strlen(value) + 2;
    data->env[index] = malloc(len);
    if (!data->env[index])
        exit(1);
    ft_strcpy(data->env[index], key);
    ft_strcpy(data->env[index] + strlen(key), "=");
    ft_strcpy(data->env[index] + strlen(key) + 1, value);
}

void add_new_env_var(t_data *data, char *key, char *value)
{
    char **new_env;
    int i;
	int j;

	i = 0;
	j = 0;

    while (data->env[i])
        i++;
    new_env = malloc((i + 2) * sizeof(char *));
    if (!new_env)
        exit(1);

    while (j < i)
    {
        new_env[j] = data->env[j];
		j++;
    }
    new_env[i] = malloc(strlen(key) + strlen(value) + 2);
    if (!new_env[i])
        exit(1);
    ft_strcpy(new_env[i], key);
    ft_strcpy(new_env[i] + strlen(key), "=");
    ft_strcpy(new_env[i] + strlen(key) + 1, value);
    new_env[i + 1] = NULL;
    free(data->env);
    data->env = new_env;
}

int builtin_export(t_data *data, char **args)
{
    (void)args;
    t_lexer *current;
    char *key;
    char *value;
    int i;
	current = data->lexer_head->next;
    if (!current)
        return (builtin_env(data, args));
    while (current)
    {
        split_key_value(current->word, &key, &value);
        i = 0;
        while (data->env[i])
        {
            if (ft_strncmp(data->env[i], key, ft_strlen(key)) == 0 && data->env[i][ft_strlen(key)] == '=')
            {
                free(data->env[i]);
                update_env_var(data, key, value, i);
                return (0);
            }
            i++;
        }
        add_new_env_var(data, key, value);
        free(key);
        free(value);
        current = current->next;
    }
    return (0);
}
