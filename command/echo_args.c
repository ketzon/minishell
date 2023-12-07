/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 03:23:14 by fgonzale          #+#    #+#             */
/*   Updated: 2023/12/07 16:24:27 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_args(t_lexer *tmp)
{
	int	count;

	count = 0;
	while (tmp && (tmp->token == WORD || tmp->token == VAR))
	{
		if (tmp->token == VAR && tmp->join == true)
		{
			while (tmp->token == VAR && tmp->join == true)
				tmp = tmp->next;
			count++;
		}
		else
		{
			count++;
			tmp = tmp->next;
		}
	}
	return (count);
}

void	delete_token(t_lexer *node, void (*del)(void *))
{
	if (node && del && node->word)
	{
		del(node->word);
		node->word = NULL;
	}
	if (node && del && node->word_backup)
	{
		del(node->word_backup);
		node->word_backup = NULL;
	}
	if (node->previous)
		node->previous->next = node->next;
	if (node->next)
		node->next->previous = node->previous;
	free_reset_ptr(node);
}

void	delete_empty_var_args(t_lexer **lexer_lst)
{
	t_lexer	*tmp;

	tmp = *lexer_lst;
	while (tmp->token == WORD || tmp->token == VAR)
	{
		if (tmp->token == VAR && tmp->word[0] == '\0'
			&& tmp->var_exists == false)
		{
			tmp = tmp->next;
			if (tmp == (*lexer_lst)->next)
				(*lexer_lst) = (*lexer_lst)->next;
			delete_token(tmp->previous, free_reset_ptr);
		}
		else
			tmp = tmp->next;
	}
}

char	*join_variables(t_lexer **lexer_lst)
{
	t_lexer	*tmp;
	char	*str;

	tmp = *lexer_lst;
	str = ft_strdup(tmp->word);
	while (tmp->token == VAR && tmp->next->token == VAR
		&& tmp->next->join == true)
	{
		str = ft_strjoin(str, tmp->next->word);
		tmp = tmp->next;
	}
	*lexer_lst = tmp;
	return (str);
}

int	create_args_echo_mode(t_lexer **lexer_lst, t_cmd *last_cmd)
{
	int		nb_args;
	t_lexer	*tmp;
	int		i;

	i = 0;
	delete_empty_var_args(lexer_lst);
	tmp = *lexer_lst;
	nb_args = count_args(tmp);
	last_cmd->args = malloc(sizeof(char *) * (nb_args + 2));
	if (!last_cmd->args)
		return (1);
	last_cmd->args[i] = ft_strdup(last_cmd->command);
	i++;
	while (tmp->token == WORD || tmp->token == VAR)
	{
		if (tmp->join == true)
			last_cmd->args[i] = join_variables(&tmp);
		else
			last_cmd->args[i] = ft_strdup(tmp->word);
		i++;
		tmp = tmp->next;
	}
	last_cmd->args[i] = NULL;
	*lexer_lst = tmp;
	return (0);
}
