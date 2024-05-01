/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_spliting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 17:40:28 by machrist          #+#    #+#             */
/*   Updated: 2024/04/30 19:27:02 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parthing.h"

static void	check_quote(char c, bool *quote, bool *dquote)
{
	if (c == '\'' && !*dquote)
		*quote = !*quote;
	if (c == '\"' && !*quote)
		*dquote = !*dquote;
}

static int	count_word(char const *s, char *arg)
{
	size_t	i;
	size_t	res;
	bool	quote;
	bool	dquote;

	i = 0;
	res = 0;
	quote = false;
	dquote = false;
	while (s[i])
	{
		while (s[i] && is_space(s[i], arg))
			i++;
		if (s[i])
			++res;
		while (s[i] && (!is_space(s[i], arg) || quote || dquote))
		{
			check_quote(s[i], &quote, &dquote);
			if (!dquote && !quote && is_special_cpt(s, &i))
				res += 2;
			i++;
		}
	}
	return (res);
}

static size_t	len_word(char const *s, char *arg)
{
	size_t	i;
	size_t	len;
	bool	quote;
	bool	dquote;

	i = 0;
	len = 0;
	quote = false;
	dquote = false;
	while (s[i] && (!is_space(s[i], arg) || quote || dquote))
	{
		check_quote(s[i], &quote, &dquote);
		if (!dquote && !quote && is_special_cpt(s, &i))
			break ;
		len++;
		i++;
	}
	return (len);
}

static char	*crt_word(char const *s, size_t *j, char *arg)
{
	size_t	i;
	size_t	len;
	char	*word;

	len = len_word(s, arg);
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
	*j += len;
	return (word);
}

char	**ft_word_spliting(char const *s, char *arg)
{
	char	**str;
	size_t	i;
	size_t	pos;

	str = malloc(sizeof(char *) * (count_word(s, arg) + 1));
	if (!str)
		return (NULL);
	i = 0;
	pos = 0;
	while (s[i])
	{
		while (s[i] && is_space(s[i], arg))
			++i;
		if (s[i] && !is_special(s[i]))
			str[pos++] = crt_word(s + i, &i, arg);
		else if (s[i])
			str[pos++] = crt_is_special(s + i, &i);
		if (s[i] && !str[pos - 1])
			return (free_split(str, --pos), NULL);
	}
	str[pos] = NULL;
	return (str);
}
