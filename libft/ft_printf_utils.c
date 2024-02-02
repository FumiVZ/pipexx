/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:34:16 by vzuccare          #+#    #+#             */
/*   Updated: 2024/01/24 12:25:15 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long long int	ft_putcharfd_count(char c, int fd)
{
	if (write(fd, &c, 1) < 0)
		return (-1);
	return (1);
}

long long int	ft_putstrfd_count(char *str, int fd)
{
	long long int	i;

	i = 0;
	if (!str)
	{
		if (write(fd, "(null)", 6) < 0)
			return (-1);
		return (6);
	}
	while (str[i])
	{
		if (ft_putcharfd_count(str[i], fd) == -1)
			return (-1);
		i++;
	}
	return (i);
}

long long int	ft_digits(long long int n)
{
	long long int	i;

	i = 0;
	if (n < 0)
	{
		n = n * -1;
		i++;
	}
	while (n > 9)
	{
		n = n / 10;
		i++;
	}
	return (i + 1);
}

long long int	ft_putnbrfd_count(long long int n, int fd)
{
	long long int		i;

	i = 0;
	if (n == -2147483648)
	{
		if (write(fd, "-2147483648", 11) < 0)
			return (-1);
		return (11);
	}
	if (n < 0)
	{
		n = n * -1;
		if (write(fd, "-", 1) < 0)
			return (-1);
		i++;
	}
	if (n > 9)
		if (ft_putnbrfd_count((n / 10), fd) == -1)
			return (-1);
	if (ft_putcharfd_count(((n % 10) + '0'), fd) == -1)
		return (-1);
	return (ft_digits(n) + i);
}
