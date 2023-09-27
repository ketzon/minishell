/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbesson <fbesson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:35:44 by fbesson           #+#    #+#             */
/*   Updated: 2023/09/27 10:31:14 by fbesson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_len(char *str, int count, int i)
{
		int	status;

		status = 0;
		while (str[i])
		{
				if ((str[i] == '\'' || str[i] == '\"') && status == DEFAULT)
				{
						if (str[i] == '\'')
								status = SQUOTE;
						if (str[i] == '\"')
								status = DQUOTE;
						i++;
						continue ;
				}
				else if ((str[i] == '\'' && status == SQUOTE)
								|| (str[i] == '\"' && status == DQUOTE))
				{
						status = DEFAULT;
						i++;
						continue ;
				}
				count++;
				i++;
		}
		return (count + 1);
}

int	handle_quotes(t_data *data)
{
	t_lexer *input;
	input = data->lexer_head;
	while(input)
	{
		if (is_quotes(input->word) == true)
		{
			if (input->previous == NULL)
			{
					delete_quotes(&input);
					printf("%s\n", "quotes_found");	
					break;
			}
		}
		input = input->next;
	}
	return (0);
}
