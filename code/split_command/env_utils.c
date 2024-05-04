/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 05:55:14 by machrist          #+#    #+#             */
/*   Updated: 2024/05/04 05:55:46 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parthing.h>

size_t	pos_var(char *str)
{
	size_t	i;
	bool	quote;
	bool	dquote;

	i = 0;
	quote = false;
	dquote = false;
	while (str[i])
	{
		if (str[i] == '$' && !quote && get_len_name(str + i + 1))
			return (i + 1);
		if (str[i] == '\'' && !dquote)
			quote = !quote;
		if (str[i] == '\"' && !quote)
			dquote = !dquote;
		if (str[i])
			i++;
	}
	return (0);
}

int	check_env_var(char *str)
{
	size_t	i;
	bool	quote;
	bool	dquote;

	i = 0;
	quote = false;
	dquote = false;
	while (str[i])
	{
		if (str[i] == '$' && !quote && get_len_name(str + i + 1))
		{
			if (dquote)
				return (1);
			return (2);
		}
		if (str[i] == '\'' && !dquote)
			quote = !quote;
		if (str[i] == '\"' && !quote)
			dquote = !dquote;
		if (str[i])
			i++;
	}
	return (0);
}

char	*check_pattern_word(char *str)
{
	size_t	i;
	bool	quote;
	bool	dquote;

	i = 0;
	quote = false;
	dquote = false;
	while (str[i])
	{
		if ((str[i] == '*' || str[i] == '?') && !quote && !dquote)
			return (wildcard_match(str));
		if (str[i] == '\'' && !dquote)
			quote = !quote;
		if (str[i] == '\"' && !quote)
			dquote = !dquote;
		if (str[i])
			i++;
	}
	return (str);
}
