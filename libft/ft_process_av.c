/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_av.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbesson <fbesson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 12:58:38 by fbesson           #+#    #+#             */
/*   Updated: 2023/04/05 12:59:30 by fbesson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_process_av(int ac, char **av)
{
	int		i;
	char	*combined_args;
	char	*tmp;
	char	**split_args;

	i = 1;
	combined_args = ft_strdup(av[0]);
	while (i < ac)
	{
		tmp = ft_strjoin(combined_args, " ");
		free(combined_args);
		combined_args = tmp;
		tmp = ft_strjoin(combined_args, av[i]);
		free(combined_args);
		combined_args = tmp;
		i++;
	}
	split_args = ft_split(combined_args, ' ');
	free(combined_args);
	return (split_args);
}
