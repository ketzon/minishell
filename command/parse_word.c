/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 17:03:29 by fgonzale          #+#    #+#             */
/*   Updated: 2023/11/20 21:53:00 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool have_spaces(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == ' ')
			return (true);
	}
	return (false);
}

void	parse_words(t_cmd **cmd_head, t_lexer **lexer_lst)
{
	t_lexer	*tmp;
	t_cmd	*last_cmd;

	tmp = *lexer_lst;
	while (tmp && (tmp->token == VAR || tmp->token == WORD))
	{
		last_cmd = get_last_cmd(*cmd_head);
		if (tmp->previous == NULL || (tmp->previous && tmp->previous->token == PIPE) || last_cmd->command == NULL) // AJOUTER LES AUTRES CAS.
		{
			if (tmp->token == VAR && have_spaces(tmp->word) == true)
				printf("Need to split var args\n"); // CHANGER POUR SPLIT VAR.
			else
				last_cmd->command = ft_strdup(tmp->word);
			tmp = tmp->next;
		}
		else
			fill_cmd_args(&tmp, last_cmd);
	}
	*lexer_lst = tmp;
}