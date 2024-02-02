/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 19:14:57 by vzuccare          #+#    #+#             */
/*   Updated: 2023/11/23 13:41:13 by vzuccare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_exit(char **string, size_t j)
{
	size_t	i;

	i = 0;
	while (i < j)
	{
		free(string[i]);
		i++;
	}
	free(string);
	return ((char *) NULL);
}

int	is_charset(char c, char charset)
{
	if (charset == c)
		return (1);
	return (0);
}

size_t	count_word(char *s, char c)
{
	size_t	i;
	size_t	count;

	count = 0;
	i = 0;
	while (s[i])
	{
		while ((is_charset(s[i], c) == 1) && s[i])
			i++;
		if (s[i])
			count++;
		while (is_charset(s[i], c) == 0 && s[i])
			i++;
	}
	return (count);
}

char	*create_word(char **string, char *s, char c, int i)
{
	int		j;
	char	*tab;

	j = 0;
	while (is_charset(s[j], c) == 0 && s[j])
		j++;
	tab = malloc((j + 1) * sizeof(char));
	if (!tab)
		return (ft_exit(string, i));
	tab[j] = '\0';
	while (j > 0)
	{
		j--;
		tab[j] = s[j];
	}
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	size_t			i;
	char			**tab;
	size_t			len;
	size_t			j;

	i = 0;
	j = 0;
	len = count_word((char *) s, c);
	tab = malloc((len + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	while (i < len)
	{
		while (is_charset(s[j], c) == 1 && s[j])
			j++;
		tab[i] = create_word(tab, (char *) &s[j], c, i);
		if (!tab[i])
			return (NULL);
		i++;
		while (is_charset(s[j], c) == 0 && s[j])
			j++;
	}
	tab[i] = NULL;
	return (tab);
}
