/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 12:00:12 by sodahani          #+#    #+#             */
/*   Updated: 2024/12/30 15:32:43 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putnbr_unsigned(unsigned int n, int *len)
{
	if (n >= 10)
		ft_putnbr_unsigned(n / 10, len);
	ft_putchar((n % 10) + '0', len);
}

static int	handle_format(const char specifier, va_list args, int *len)
{
	char	c;

	if (specifier == 'd' || specifier == 'i')
		ft_putnbr(va_arg(args, int), len);
	else if (specifier == 's')
		ft_putstr(va_arg(args, char *), len);
	else if (specifier == 'c')
	{
		c = (char)va_arg(args, int);
		ft_putchar(c, len);
	}
	else if (specifier == 'p')
		ft_putptr(va_arg(args, void *), len);
	else if (specifier == 'x')
		ft_puthex(va_arg(args, unsigned int), 0, len);
	else if (specifier == 'X')
		ft_puthex(va_arg(args, unsigned int), 1, len);
	else if (specifier == 'u')
		ft_putnbr_unsigned(va_arg(args, unsigned int), len);
	else if (specifier == '%')
		ft_putchar('%', len);
	else
		return (-1);
	return (0);
}

int	ft_printf(const char *format, ...)
{
	int		len;
	va_list	args;

	if ((write(1, 0, 0) == -1) || format == NULL)
		return (-1);
	len = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			if (*(format + 1) == '\0')
				return (-1);
			format++;
			if (handle_format(*format, args, &len) == -1)
				return (-1);
		}
		else
			ft_putchar(*format, &len);
		format++;
	}
	va_end(args);
	return (len);
}
