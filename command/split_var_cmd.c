/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_var_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:48:08 by fgonzale          #+#    #+#             */
/*   Updated: 2023/12/07 23:21:16 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	split_var_cmd(char *var_str, t_cmd *last_cmd)
{
	int		i;
	char	**var_splitted;
	t_lexer	*tmp_lexer;
	t_lexer	*tmp_save_free;

	tmp_lexer = NULL;
	i = 1;
	var_splitted = ft_split(var_str, ' ');
	if (!var_splitted || var_splitted[0] == NULL)
	{
		last_cmd->command = ft_strdup("");
		free_env_array(var_splitted);
		return ;
	}
	last_cmd->command = ft_strdup(var_splitted[0]);
	if (var_splitted[1])
		tmp_lexer = new_node(ft_strdup(var_splitted[1]), NULL, WORD);
	tmp_save_free = tmp_lexer;
	while (var_splitted[i++])
		stack_add_bottom(&tmp_lexer, new_node(ft_strdup(var_splitted[i]),
				NULL, WORD));
	stack_add_bottom(&tmp_lexer, new_node(NULL, NULL, END));
	fill_cmd_args(&tmp_lexer, last_cmd);
	clear_lexer_head(&tmp_save_free);
	free_env_array(var_splitted);
}
