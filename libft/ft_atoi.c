/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 08:01:27 by vzuccare          #+#    #+#             */
/*   Updated: 2024/01/29 14:31:51 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long int	ft_strtol(const char *str)
{
	int			signe;
	size_t		i;
	long int	va;

	i = 0;
	va = 0;
	signe = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			signe = -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (va != ((va * 10) + str[i] - '0') / 10)
		{
			ft_putstr_fd("Error\n", 1);
			exit(0);
		}
		va = va * 10 + str[i] - '0';
		i++;
	}
	return (va * signe);
}

int	ft_atoi(const char *nptr)
{
	return ((int)ft_strtol(nptr));
}
