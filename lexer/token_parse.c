/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 00:29:16 by fgonzale          #+#    #+#             */
/*   Updated: 2023/12/09 18:53:44 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_sep(char *str, int i)
{
	int	type;

	if (str[i] == ' ' || (str[i] > 8 && str[i] < 14))
		type = SPACES;
	else if (str[i] == '|')
		type = PIPE;
	else if (str[i] == '<' && str[i + 1] == '<')
		type = HEREDOC;
	else if (str[i] == '>' && str[i + 1] == '>')
		type = OUTAPPEND;
	else if (str[i] == '<')
		type = INPUT;
	else if (str[i] == '>')
		type = OUTPUT;
	else if (str[i] == '\0')
		type = END;
	else
		type = 0;
	return (type);
}

static int	save_input(t_data *data, int start, int *i)
{
	int		type;
	char	*str;
	char	*word;

	str = data->line;
	type = is_sep(str, (*i));
	if (type)
	{
		if ((*i) != 0 && is_sep(str, (*i) - 1) == 0)
		{
			word = ft_substr(str, start, (*i) - start);
			stack_add_bottom(&data->lexer_head,
				new_node(word, ft_strdup(word), WORD));
		}
		if (type == OUTAPPEND || type == HEREDOC || type == PIPE
			|| type == INPUT || type == OUTPUT || type == END)
		{
			add_token(str, *i, &data->lexer_head);
			if (type == OUTAPPEND || type == HEREDOC)
				(*i)++;
		}
		start = (*i) + 1;
	}
	return (start);
}

int	get_status(int status, char c)
{
	if (c == '\'' && status == DEFAULT)
		status = SQUOTE;
	else if (c == '\"' && status == DEFAULT)
		status = DQUOTE;
	else if (c == '\'' && status == SQUOTE)
		status = DEFAULT;
	else if (c == '\"' && status == DQUOTE)
		status = DEFAULT;
	return (status);
}

int	token_parse(t_data *data)
{
	int	i;
	int	len;
	int	start;
	int	status;

	i = -1;
	len = ft_strlen(data->line);
	start = 0;
	status = DEFAULT;
	while (++i <= len)
	{
		status = get_status(status, data->line[i]);
		if (status == DEFAULT)
			start = save_input(data, start, &i);
	}
	if (status != DEFAULT)
	{
		if (status == DQUOTE)
			errmsg("unexpected EOF while looking for matching", "\"", true);
		else if (status == SQUOTE)
			errmsg("unexpected EOF while looking for matching", "\'", true);
		errmsg("syntax error", "unexpected end of file", false);
		return (1);
	}
	return (0);
}

char	*token_word(t_token token)
{
	if (token == WORD)
		return ("WORD");
	else if (token == VAR)
		return ("VAR");
	else if (token == PIPE)
		return ("PIPE");
	else if (token == INPUT)
		return ("INPUT");
	else if (token == HEREDOC)
		return ("HEREDOC");
	else if (token == OUTPUT)
		return ("OUTPUT");
	else if (token == OUTAPPEND)
		return ("OUTAPPEND");
	else if (token == END)
		return ("END");
	else
		return ("");
}
