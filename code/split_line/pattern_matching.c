/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_matching.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:39:48 by machrist          #+#    #+#             */
/*   Updated: 2024/03/16 14:50:21 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parthing.h"

static char	*check_pattern_word(char *str)
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

void	pattern_matching(char **str)
{
	size_t	i;
	char	*tmp;

	i = 0;
	while (str[i])
	{
		tmp = check_pattern_word(str[i]);
		if (ft_strncmp(tmp, str[i], ft_strlen(str[i]) + 1))
		{
			free(str[i]);
			str[i] = tmp;
		}
		i++;
	}
}
