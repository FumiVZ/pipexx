/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:43:44 by vzuccare          #+#    #+#             */
/*   Updated: 2023/12/04 17:50:24 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long long int	printaddress(size_t adress)
{
	char			c;
	long long int	total;

	total = 0;
	if (adress >= 16)
	{
		total += printaddress(adress / 16);
		total += printaddress(adress % 16);
	}
	else
	{
		c = (adress % 16) + '0';
		if ((adress % 16) > 9)
			c = (adress % 16) - 10 + 'a';
		if (write(1, &c, 1) < 0)
			return (-1);
		total++;
	}
	return (total);
}

long long int	print_pointer(size_t adress)
{
	long long int	total;

	total = 0;
	if (adress == 0)
	{
		if (write(1, "(nil)", 5) < 0)
			return (-1);
		return (5);
	}
	if (write(1, "0x", 2) < 0)
		return (-1);
	total += 2;
	total += printaddress(adress);
	return (total);
}

long long int	ft_putx(long long int nbr, char *base, int fd)
{
	int					len;
	long long int		i;

	i = 0;
	len = 0;
	while (base[len])
		len++;
	if (nbr < 0)
	{
		if (ft_putcharfd_count('-', fd) == -1)
			return (-1);
		nbr = -nbr;
	}
	if (nbr / len != 0)
	{
		i = ft_putx(nbr / len, base, fd);
		if (i == -1)
			return (-1);
	}
	if (ft_putcharfd_count(base[nbr % len], fd) == -1)
		return (-1);
	i++;
	return (i);
}
