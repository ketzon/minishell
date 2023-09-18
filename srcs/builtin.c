/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbesson <fbesson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:31:38 by fbesson           #+#    #+#             */
/*   Updated: 2023/09/18 16:46:35 by fbesson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


/* int	builtin_env(t_data *data) */
/* { */
/* 	int i; */
/* 	char **env_vars; */

/* 	env_vars = data->env->env_vars; */
/* 	i = 0; */
/* 	while (env_vars && env_vars[i]) */
/* 	{ */
/* 			printf("%s\n", env_vars[i]); */
/* 			i++; */
/* 	} */
/* 	return (0); */
/* } */
int	builtin_echo(t_data *data)
{
	t_lexer *current;
	current = data->lexer_head->next;

	while (current)
	{
		ft_putstr(current->word);
		if (current->next)
			ft_putchar(' ');
		current = current->next;
	}
	ft_putchar('\n');
	return (0);
}

t_builtin builtins[] = 
{
		{"echo", builtin_echo},
		/* {"env", builtin_env}, */
		{NULL, NULL}
};

int	execute_builtin(t_data *data)
{
	int i;
	char *command_name;
	command_name = data->lexer_head->word;

	i = 0;
	while (builtins[i].name)
	{
		if (ft_strcmp(command_name, builtins[i].name) == 0)
			return (builtins[i].func(data));
		i++;
	}
	return (NOT_FIND);
}
