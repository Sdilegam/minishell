/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkasmi <abkasmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:34:01 by abkasmi           #+#    #+#             */
/*   Updated: 2021/10/07 14:48:12 by abkasmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_hex(char c, int i, unsigned int value)
{
	if (c == 'x')
		return (print_hexa(i, value));
	return (print_upper_hexa(i, value));
}

int	print_unsigned_decimal(unsigned int i, unsigned int int_value)
{
	i++;
	if (int_value > 9)
	{
		i = print_unsigned_decimal(i, int_value / 10);
		print_unsigned_decimal(i, int_value % 10);
	}
	else
	{
		print_char(48 + int_value);
	}
	return (i);
}

int	print_hexa(int i, unsigned long int_value)
{
	i++;
	if (int_value > 9 && int_value < 16)
	{
		if (int_value == 10)
			write(1, "a", 1);
		else if (int_value == 11)
			write(1, "b", 1);
		else if (int_value == 12)
			write(1, "c", 1);
		else if (int_value == 13)
			write(1, "d", 1);
		else if (int_value == 14)
			write(1, "e", 1);
		else if (int_value == 15)
			write(1, "f", 1);
	}
	else if (int_value > 15)
	{
		i = print_hexa(i, int_value / 16);
		print_hexa(i, int_value % 16);
	}
	else
		print_char(48 + int_value);
	return (i);
}

int	print_upper_hexa(int i, unsigned int int_value)
{
	i++;
	if (int_value > 9 && int_value < 16)
	{
		if (int_value == 10)
			write(1, "A", 1);
		else if (int_value == 11)
			write(1, "B", 1);
		else if (int_value == 12)
			write(1, "C", 1);
		else if (int_value == 13)
			write(1, "D", 1);
		else if (int_value == 14)
			write(1, "E", 1);
		else if (int_value == 15)
			write(1, "F", 1);
	}
	else if (int_value > 15)
	{
		i = print_upper_hexa(i, int_value / 16);
		print_upper_hexa(i, int_value % 16);
	}
	else
		print_char(48 + int_value);
	return (i);
}

int	print_adress(int i, void *value)
{
	unsigned long	ptr_value;

	ptr_value = (unsigned long)value;
	write(1, "0x", 2);
	i += print_hexa(0, ptr_value);
	return (i);
}
