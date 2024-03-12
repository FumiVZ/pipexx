/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:34:05 by machrist          #+#    #+#             */
/*   Updated: 2024/02/22 14:08:38 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	is_word(char const *s)
{
	if (!s)
		return (0);
	if (s[0] == '\'' && s[1] == '\'')
		return (0);
	if (s[0] == '\"' && s[1] == '\"')
		return (0);
	return (1);
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
		while (s[i] && s[i] == ' ')
			++i;
		if (s[i] && is_word(s + i))
			++res;
		if (s[i] && s[i] != ' ')
			i += len_word_tot(s + i, s[i], i);
	}
	return (res);
}

static char	*ft_trim_word(char *word)
{
	char	*tmp;

	tmp = word;
	if (!word)
		return (NULL);
	if (word[0] == '\"')
	{
		word = ft_strtrim(word, "\"");
		free(tmp);
		return (word);
	}
	if (word[0] == '\'')
	{
		word = ft_strtrim(word, "\'");
		free(tmp);
		return (word);
	}
	return (word);
}

static char	*crt_word(char const *s)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*word;

	if (!s || !is_word(s))
		return (NULL);
	i = 0;
	len = len_word(s, s[0], i);
	word = malloc(len + 1);
	if (!word)
		return (NULL);
	i = 0;
	j = 0;
	while (j < len)
	{
		if (s[i] == '\\' && has_bs(s, i + 1) && (s[i + 1] == '\'' || \
			s[i + 1] == '\"' || s[i + 1] == '\\' || s[i + 1] == ' '))
			i++;
		word[j++] = s[i++];
	}
	word[len] = '\0';
	if (s[0] == '\"' || s[0] == '\'')
		word = ft_trim_word(word);
	return (word);
}

char	**ft_split_command(char const *s)
{
	char	**str;
	size_t	i;
	size_t	pos;

	if (!s || !count_word(s))
		return (NULL);
	str = malloc(sizeof(char *) * (count_word(s) + 1));
	if (!str)
		return (NULL);
	i = 0;
	pos = 0;
	while (s[i])
	{
		while (s[i] && s[i] == ' ')
			++i;
		if (s[i] && is_word(s + i))
		{
			str[pos] = crt_word(s + i);
			if (!str[pos++])
				return (free_split(str, --pos), NULL);
		}
		i += len_word_tot(s + i, s[i], i);
	}
	str[pos] = NULL;
	return (str);
}
