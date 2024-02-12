/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:20:48 by vzuccare          #+#    #+#             */
/*   Updated: 2024/02/12 15:19:09 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long long int	ft_percent_case(int fd, const char *format, va_list args)
{
	long long int	i;

	i = 0;
	if (*format == '%')
		i = ft_putcharfd_count('%', fd);
	else if (*format == 'c')
		i = ft_putcharfd_count(va_arg(args, int), fd);
	else if (*format == 's')
		i = ft_putstrfd_count(va_arg(args, char *), fd);
	else if (*format == 'p')
		i = print_pointer(va_arg(args, long long int));
	else if (*format == 'd' || *format == 'i')
		i = ft_putnbrfd_count(va_arg(args, int), fd);
	else if (*format == 'u')
		i = ft_putnbrfd_count(va_arg(args, unsigned int), fd);
	else if (*format == 'x')
		i = ft_putx(va_arg(args, unsigned int), "0123456789abcdef", fd);
	else if (*format == 'X')
		i = ft_putx(va_arg(args, unsigned int), "0123456789ABCDEF", fd);
	else
		i = ft_putcharfd_count(*format, fd);
	return (i);
}

int	ft_printf_iterate(int fd, const char *format, va_list args)
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
			if (ft_putcharfd_count(*format, fd) == -1)
				return (-1);
			i++;
		}
		else
		{
			temp = ft_percent_case(fd, ++format, args);
			if (temp == -1)
				return (-1);
			i += temp;
		}
		format++;
	}
	return (i);
}

int	ft_printf(int fd, const char *format, ...)
{
	va_list		args;
	long long	i;

	i = 0;
	va_start(args, format);
	if (format == NULL)
		return (0);
	i = ft_printf_iterate(fd, format, args);
	va_end(args);
	return (i);
}
