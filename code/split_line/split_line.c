/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 20:29:35 by machrist          #+#    #+#             */
/*   Updated: 2024/02/21 22:45:52 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// << < > >> || | && & "" '' ; ``

int	command_end(char c)
{
	if (c == ';' || c == '|' || c == '&' || c == '\0')
		return (1);
	return (0);
}

static int	count_word(char const *s)
{
	size_t	i;
	size_t	res;

	if (!s)
		return (0);
	i = 0;
	res = 0;
	while (s[i])
	{
		while (s[i] && command_end(s[i]))
			i++;
		while (s[i] && s[i] == ' ')
			i++;
		if (s[i])
			++res;
		while (s[i] && !command_end(s[i]))
		{
			if (s[i] == '\'' || s[i] == '\"')
				i += ft_len_word(s + i, s[i], i);
			else
				++i;
		}
	}
	return (res);
}

static char	*crt_word(char const *s)
{
	size_t	i;
	size_t	len;
	char	*word;

	if (!s)
		return (NULL);
	len = 0;
	while (s[len] && !command_end(s[len]))
	{
		if (s[len] == '\'' || s[len] == '\"')
			len += ft_len_word(s + len, s[len], len);
		else
			len++;
	}
	word = malloc(sizeof(char) * len + 1);
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

size_t	add_word(char **str, char const *s, size_t *pos, size_t *i)
{
	while (s[*i] && command_end(s[*i]))
		++(*i);
	while (s[*i] && s[*i] == ' ')
		++(*i);
	if (s[*i])
	{
		str[*pos] = crt_word(s + *i);
		if (!str[*pos])
		{
			free_split(str, *pos);
			return (0);
		}
		++(*pos);
	}
	while (s[*i] && !command_end(s[*i]))
	{
		if (s[*i] == '\'' || s[*i] == '\"')
			*i += ft_len_word(s + *i, s[*i], *i);
		else
			++(*i);
	}
	return (*i);
}

char	**ft_split_line(char const *s)
{
	char	**str;
	size_t	i;
	size_t	pos;

	if (!s)
		return (NULL);
	str = malloc(sizeof(char *) * (count_word(s) + 1));
	if (!str)
		return (NULL);
	i = 0;
	pos = 0;
	while (s[i])
	{
		i = add_word(str, s, &pos, &i);
		if (!i)
			return (NULL);
	}
	str[pos] = NULL;
	return (str);
}
