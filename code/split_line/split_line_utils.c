/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 20:33:03 by machrist          #+#    #+#             */
/*   Updated: 2024/02/21 22:45:14 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	has_bs(const char *s, size_t i)
{
	size_t	count;

	if (!s || i == 0)
		return (0);
	if (s[i] != '\'' && s[i] != '\"' && s[i] != '\\' && s[i] != ' ')
		return (0);
	count = 0;
	while (s[i - 1] == '\\')
	{
		count++;
		i--;
		if (i == 0)
			return (count % 2);
	}
	return (count % 2);
}

int	ft_len_word(char const *s, char c, size_t i)
{
	i = 0;
	if (c != '\'' && c != '\"' )
	{
		while ((s[i] && !command_end(s[i])) || (s[i] == ' ' && has_bs(s, i)))
			++i;
		return (i);
	}
	else
	{
		i++;
		while ((s[i] && s[i] != c) || (s[i] == c && has_bs(s, i)))
			++i;
		return (i + 1);
	}
}
