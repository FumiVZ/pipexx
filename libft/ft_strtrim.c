/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:54:43 by vzuccare          #+#    #+#             */
/*   Updated: 2023/11/15 22:34:21 by vzuccare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_charset(const char	*set, char c)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	size_t	size;
	char	*str;

	i = 0;
	size = ft_strlen(s1);
	j = 0;
	while (s1[i] && is_charset(set, s1[i]))
		i++;
	while (size > i && is_charset(set, s1[size - 1]))
		size--;
	str = malloc(sizeof(char) * (size - i + 1));
	if (!str)
		return (NULL);
	while (i < size)
	{
		str[j] = s1[i];
		i++;
		j++;
	}
	str[j] = '\0';
	return (str);
}
