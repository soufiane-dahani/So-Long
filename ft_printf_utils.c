/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 12:01:27 by sodahani          #+#    #+#             */
/*   Updated: 2025/01/07 14:01:10 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar(char c, int *len)
{
	write(1, &c, 1);
	(*len)++;
}

void	ft_putstr(const char *str, int *len)
{
	if (!str)
		str = "(null)";
	while (*str)
	{
		ft_putchar(*str, len);
		str++;
	}
}

void	ft_putnbr(int n, int *len)
{
	if (n == -2147483648)
	{
		ft_putchar('-', len);
		ft_putchar('2', len);
		ft_putnbr(147483648, len);
		return ;
	}
	if (n < 0)
	{
		ft_putchar('-', len);
		n = -n;
	}
	if (n >= 10)
	{
		ft_putnbr(n / 10, len);
	}
	ft_putchar(n % 10 + '0', len);
}

void	ft_puthex(unsigned long n, int uppercase, int *len)
{
	char	*hex_digits;

	if (uppercase)
		hex_digits = "0123456789ABCDEF";
	else
		hex_digits = "0123456789abcdef";
	if (n >= 16)
	{
		ft_puthex(n / 16, uppercase, len);
	}
	ft_putchar(hex_digits[n % 16], len);
}

void	ft_putptr(void *ptr, int *len)
{
	unsigned long	address;

	if (!ptr)
	{
		ft_putstr("(nil)", len);
		return ;
	}
	address = (unsigned long)ptr;
	ft_putstr("0x", len);
	ft_puthex(address, 0, len);
}
