/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:20:48 by vzuccare          #+#    #+#             */
/*   Updated: 2024/01/24 12:24:57 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long long int	ft_percent_case(const char *format, va_list args)
{
	long long int	i;

	i = 0;
	if (*format == '%')
		i = ft_putcharfd_count('%', 1);
	else if (*format == 'c')
		i = ft_putcharfd_count(va_arg(args, int), 1);
	else if (*format == 's')
		i = ft_putstrfd_count(va_arg(args, char *), 1);
	else if (*format == 'p')
		i = print_pointer(va_arg(args, long long int));
	else if (*format == 'd' || *format == 'i')
		i = ft_putnbrfd_count(va_arg(args, int), 1);
	else if (*format == 'u')
		i = ft_putnbrfd_count(va_arg(args, unsigned int), 1);
	else if (*format == 'x')
		i = ft_putx(va_arg(args, unsigned int), "0123456789abcdef", 1);
	else if (*format == 'X')
		i = ft_putx(va_arg(args, unsigned int), "0123456789ABCDEF", 1);
	else
		i = ft_putcharfd_count(*format, 1);
	return (i);
}

int	ft_printf_iterate(const char *format, va_list args)
{
	long long	i;
	long long	temp;

	i = 0;
	temp = 0;
	while (*format)
	{
		if (*format == '\0')
			break ;
		if (*format != '%')
		{
			if (ft_putcharfd_count(*format, 1) == -1)
				return (-1);
			i++;
		}
		else
		{
			temp = ft_percent_case(++format, args);
			if (temp == -1)
				return (-1);
			i += temp;
		}
		format++;
	}
	return (i);
}

int	ft_printf(const char *format, ...)
{
	va_list		args;
	long long	i;

	i = 0;
	va_start(args, format);
	if (format == NULL)
		return (0);
	i = ft_printf_iterate(format, args);
	va_end(args);
	return (i);
}
