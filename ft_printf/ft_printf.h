/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkasmi <abkasmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 13:34:43 by abkasmi           #+#    #+#             */
/*   Updated: 2021/10/07 14:45:48 by abkasmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

int	ft_printf(const char *str, ...);
int	check_format(const char *str, va_list arg);
int	print_char(char value);
int	print_str(char *value);
int	print_decimal(int i, int int_value);
int	print_upper_hexa(int i, unsigned int int_value);
int	print_unsigned_decimal(unsigned int i, unsigned int int_value);
int	print_char(char value);
int	print_hexa(int i, unsigned long int_value);
int	print_adress(int i, void *value);
int	print_hex(char c, int i, unsigned int value);

#endif