/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 16:02:29 by fbesson           #+#    #+#             */
/*   Updated: 2023/09/04 15:48:00 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H

# define PRINTF_H
# define HEX_BASE "0123456789abcdef0123456789ABCDEF"

# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>

int		ft_printf(const char *format, ...);
int		ft_conversions(const char c, va_list *list);

int		ft_putchar(int c);
int		ft_putstr(const char *str);
int		ft_putnbr(unsigned long nb, unsigned int base, int X);
int		ft_putdecimal(va_list *args);
int		ft_putptr(va_list *args);

#endif
