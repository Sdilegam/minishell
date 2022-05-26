/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkasmi <abkasmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:29:09 by abkasmi           #+#    #+#             */
/*   Updated: 2021/10/07 15:02:53 by abkasmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_decimal(int i, int int_value)
{
	i++;
	if (int_value == -2147483648)
	{
		write(1, "-2147483648", 11);
		return (11);
	}
	else if (int_value < 0)
	{
		write(1, "-", 1);
		i = print_decimal(i, int_value * (-1));
	}
	else if (int_value > 9)
	{
		i = print_decimal(i, int_value / 10);
		print_decimal(i, int_value % 10);
	}
	else
	{
		print_char(48 + int_value);
	}
	return (i);
}

int	print_char(char value)
{
	write(1, &value, 1);
	return (1);
}

int	print_str(char *value)
{
	int	j;

	if (!value)
	{
		write(1, "(null)", 6);
		return (6);
	}
	j = 0;
	while (value[j])
	{
		write(1, &value[j], 1);
		j++;
	}
	return (j);
}

int	check_format(const char *str, va_list arg)
{
	int	count;

	count = 0;
	if (*(str + 1) == 'c')
		count = print_char(va_arg(arg, int));
	else if (*(str + 1) == 's')
		count = print_str(va_arg(arg, char *));
	else if (*(str + 1) == 'd' || *(str + 1) == 'i')
		count = print_decimal(0, va_arg(arg, int));
	else if (*(str + 1) == '%')
		count = print_char('%');
	else if (*(str + 1) == 'u')
		count = print_unsigned_decimal(0, va_arg(arg, unsigned int));
	else if (*(str + 1) == 'x' || *(str + 1) == 'X')
		count = print_hex(*(str + 1), 0, va_arg(arg, unsigned int));
	else if (*(str + 1) == 'p')
		count = print_adress(2, va_arg(arg, void *));
	return (count);
}

int	ft_printf(const char *str, ...)
{
	va_list	arg;
	int		i;
	int		count;

	i = 0;
	count = 0;
	va_start(arg, str);
	while (str[i])
	{
		if (str[i] != '%')
		{
			write(1, &str[i], 1);
			i++;
			count++;
		}
		else
		{
			count += check_format(str + i, arg);
			i += 2;
		}
	}
	va_end(arg);
	return (count);
}
