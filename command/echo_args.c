/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 03:23:14 by fgonzale          #+#    #+#             */
/*   Updated: 2023/12/04 17:17:19 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	count_args(t_lexer *tmp)
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

static void	delete_token(t_lexer *node, void (*del)(void *))
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
	t_lexer *tmp;

	tmp = *lexer_lst;
	while (tmp->token == WORD || tmp->token == VAR)
	{
		if (tmp->token == VAR && tmp->word[0] == '\0' && tmp->var_exists == false)
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

static char	*join_variables(t_lexer **lexer_lst)
{
	t_lexer	*tmp;
	char	*str;

	tmp = *lexer_lst;
	str = ft_strdup(tmp->word);
	while (tmp->token == VAR && tmp->next->token == VAR && tmp->next->join == true)
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

char	**copy_to_new_tab(int len, char **new_tab, t_cmd *last_cmd, t_lexer *tmp)
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
	return(new_tab);
}
