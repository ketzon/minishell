/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_args2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:21:57 by fgonzale          #+#    #+#             */
/*   Updated: 2023/12/07 16:25:33 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	add_args_echo_mode(t_lexer **lexer_lst, t_cmd *last_cmd)
{
	int		len;
	int		nb_args;
	char	**new_tab;
	t_lexer	*tmp;

	delete_empty_var_args(lexer_lst);
	tmp = *lexer_lst;
	nb_args = count_args(tmp);
	len = 0;
	while (last_cmd->args[len])
		len++;
	new_tab = malloc(sizeof(char *) * (nb_args + len + 1));
	if (!new_tab)
		return (1);
	new_tab = copy_to_new_tab(len, new_tab, last_cmd, tmp);
	free(last_cmd->args);
	last_cmd->args = new_tab;
	while (tmp->token == WORD || tmp->token == VAR)
		tmp = tmp->next;
	*lexer_lst = tmp;
	return (0);
}

char	**copy_to_new_tab(int len, char **new_tab,
		t_cmd *last_cmd, t_lexer *tmp)
{
	int	i;

	i = 0;
	while (i < len)
	{
		new_tab[i] = last_cmd->args[i];
		i++;
	}
	while (tmp->token == WORD || tmp->token == VAR)
	{
		if (tmp->join == true)
			new_tab[i] = join_variables(&tmp);
		else
			new_tab[i] = ft_strdup(tmp->word);
		i++;
		tmp = tmp->next;
	}
	new_tab[i] = NULL;
	return (new_tab);
}
