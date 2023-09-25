/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbesson <fbesson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:06:03 by fbesson           #+#    #+#             */
/*   Updated: 2023/09/20 12:06:14 by fbesson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

int builtin_exit(t_data *data)
{
	int exit_value;
    t_lexer *current;
    current = data->lexer_head->next;

    if (!current)
    {
        printf("exit\n");
        exit(0);
    }
    else
    {
        exit_value = ft_atoi(current->word);
        printf("exit\n");
        exit(exit_value);
    }
    return (0);
}
