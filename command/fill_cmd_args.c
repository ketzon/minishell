/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 20:04:40 by fgonzale          #+#    #+#             */
/*   Updated: 2023/12/05 22:21:10 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_cmd_args(t_lexer *lexer_lst)
{
	int	count;

	count = 0;
	while (lexer_lst && (lexer_lst->token == WORD || lexer_lst->token == VAR))
	{
		count++;
		lexer_lst = lexer_lst->next;
	}
	return (count);
}

int	create_args(t_cmd *last_cmd, t_lexer **lexer_lst)
{
	int		i;
	int		args_count;
	t_lexer	*tmp;

	tmp = *lexer_lst;
	i = 0;
	args_count = count_cmd_args(tmp);
	last_cmd->args = malloc((args_count + 2) * sizeof(char *));
	if (last_cmd->args == NULL)
		return (1);
	last_cmd->args[i] = ft_strdup(last_cmd->command);
	i++;
	while (tmp && (tmp->token == WORD || tmp->token == VAR))
	{
		last_cmd->args[i] = ft_strdup(tmp->word);
		i++;
		tmp = tmp->next;
	}
	last_cmd->args[i] = NULL;
	*lexer_lst = tmp;
	return (0);
}

int	add_new_args(t_cmd *last_cmd, t_lexer **lexer_lst)
{
	t_lexer	*tmp;
	char	**new_args_tab;
	int		old_args_count;
	int		args_count;

	tmp = *lexer_lst;
	old_args_count = 0;
	while (tmp && (tmp->token == WORD || tmp->token == VAR))
	{
		args_count++;
		tmp = tmp->next;
	}
	while (last_cmd->args[old_args_count])
		args_count++;
	new_args_tab = malloc((old_args_count + args_count + 1) * sizeof(char *));
	if (!new_args_tab)
		return (1);
	new_args_tab = fill_args_tab(last_cmd, lexer_lst, new_args_tab, old_args_count);
	free(last_cmd->args);
	last_cmd->args = new_args_tab;
	*lexer_lst = tmp;
	return (0);
}

char	**fill_args_tab(t_cmd *last_cmd, t_lexer **lexer_lst, char **new_args_tab, int old_args_count)
{
	int		i;
	t_lexer	*tmp;

	tmp = *lexer_lst;
	i = 0;
	while (i < old_args_count)
	{
		new_args_tab[i] = last_cmd->args[i];
		i++;
	}
	while (tmp && (tmp->token == WORD || tmp->token == VAR))
	{
		new_args_tab[i] = ft_strdup(tmp->word);
		i++;
		tmp = tmp->next;
	}
	new_args_tab[i] = NULL;
	return (new_args_tab);
}

int	fill_cmd_args(t_lexer **lexer_lst, t_cmd *last_cmd)
{
	if (ft_strcmp(last_cmd->command, "echo") == 0)
	{
		if (last_cmd->args == NULL)
			return (create_args_echo_mode(lexer_lst, last_cmd));
		else
			return (add_args_echo_mode(lexer_lst, last_cmd));
	}
	if (last_cmd && last_cmd->args == NULL)
		return (create_args(last_cmd, lexer_lst));
	else
		return (add_new_args(last_cmd, lexer_lst));
	return (0);
}
