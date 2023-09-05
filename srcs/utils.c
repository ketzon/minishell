/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 17:44:56 by fgonzale          #+#    #+#             */
/*   Updated: 2023/09/05 17:03:30 by fbesson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* SAUTE LES ESPACES DANS UNE STRING ET RENVOIE DE COMBIEN IL A AVANCE */
int ft_skip_white_spaces(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0' && str[i] == ' ')
        i++;
    return (i);
}
