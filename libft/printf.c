/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbesson <fbesson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 14:22:50 by fbesson           #+#    #+#             */
/*   Updated: 2022/12/14 15:47:49 by fbesson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int	ft_conversions(const char c, va_list *args)
{
	if (c == 'c')
		return (ft_putchar(va_arg(*args, int)));
	if (c == 's')
		return (ft_putstr(va_arg(*args, char *)));
	if (c == 'p')
		return (ft_putptr(args));
	if (c == 'd' || c == 'i')
		return (ft_putdecimal(args));
	if (c == 'u')
		return (ft_putnbr(va_arg(*args, unsigned int), 10, 0));
	if (c == 'x' || c == 'X')
		return (ft_putnbr(va_arg(*args, unsigned int), 16, c == 'X'));
	if (c == '%')
		return (ft_putchar('%'));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	size_t		i;
	size_t		len_output;
	va_list		args;

	i = -1;
	len_output = 0;
	va_start(args, format);
	while (format[++i])
	{
		if (format[i] == '%')
			len_output += ft_conversions(format[++i], &args);
		else
			len_output += ft_putchar(format[i]);
	}
	va_end(args);
	return (len_output);
}
