/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_spliting_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 14:27:24 by machrist          #+#    #+#             */
/*   Updated: 2024/04/30 19:22:25 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parthing.h"

bool	is_space(char c, char *arg)
{
	size_t	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == c)
			return (true);
		++i;
	}
	return (false);
}

bool	is_special(char c)
{
	return (c == '|' || c == '&' || c == '<' || c == '>' || c == '('
		|| c == ')');
}

bool	is_special_cpt(char const *c, size_t *i)
{
	if (c[*i] == '|' || c[*i] == '&' || c[*i] == '<' || c[*i] == '>'
		|| c[*i] == '(' || c[*i] == ')')
	{
		while (c[*i] == c[*i + 1] && !(c[*i] == '(' || c[*i] == ')'))
			++*i;
		return (true);
	}
	return (false);
}

char	*crt_is_special(char const *s, size_t *j)
{
	size_t	len;
	size_t	i;
	char	*word;

	len = 1;
	while (s[len] == s[len - 1] && !(s[len] == '(' || s[len] == ')'))
		++len;
	word = malloc(sizeof(char) * len + 1);
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = s[i];
		++i;
	}
	word[i] = '\0';
	*j += len;
	return (word);
}
