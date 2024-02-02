/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:37:47 by vzuccare          #+#    #+#             */
/*   Updated: 2023/11/14 14:50:50 by vzuccare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp( const void *s1, const void *s2, size_t n )
{
	size_t			i;
	unsigned char	*cpointer1;
	unsigned char	*cpointer2;

	i = 0;
	cpointer1 = (unsigned char *)s1;
	cpointer2 = (unsigned char *)s2;
	while (i < n)
	{
		if (cpointer1[i] != cpointer2[i])
			return (cpointer1[i] - cpointer2[i]);
		i++;
	}
	return (0);
}
