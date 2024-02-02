/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:35:03 by vzuccare          #+#    #+#             */
/*   Updated: 2023/11/09 14:37:15 by vzuccare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void	*s, int c, size_t n)
{
	size_t			i;
	unsigned char	*cmemoryblock;

	i = 0;
	cmemoryblock = (unsigned char *)s;
	while (cmemoryblock + i < (unsigned char *)s + n)
	{
		if (cmemoryblock[i] == (unsigned char) c)
			return ((void *)cmemoryblock + i);
		i++;
	}
	return (NULL);
}
