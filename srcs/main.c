/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:30:50 by fgonzale          #+#    #+#             */
/*   Updated: 2023/09/14 19:56:49 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool    parse_input(t_data *data)
{
    char *tmp;
    
    tmp = ft_strtrim(data->line, " ");
    free(data->line);
    data->line = tmp;
    if (data->line == NULL)
        exit(1); // PEUT ETRE CHANGER POUR EXIT BUILTIN
    if (*data->line == '\0')
        return (false);
    if (closed_quotes(data->line) == false)
        return (ft_error(2), false);
    add_history(data->line);
    lexer(data);
    if (!variable_check(data))
        return (false);
    //CHECK IF VARIABLES(data->lexer_head);
    return (true);
}

void    reset_loop(t_data *data)
{
    if (data->line)
        free(data->line);
}

int main(int argc, char **argv, char **envp)
{
    t_data  data;
    (void)argc;
    (void)argv;
    
    data.env_paths = get_env_path(envp);
    
    while (1)
    {
        signals_handling();
        data.line = readline(PROMPT);
        if (parse_input(&data) == true)
            printf("Valid input\n");
        else
            printf("Invalid input\n");
        reset_loop(&data);
    }
}
