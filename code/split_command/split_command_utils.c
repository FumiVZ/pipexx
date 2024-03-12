/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:45:05 by machrist          #+#    #+#             */
/*   Updated: 2024/02/21 22:43:25 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	len_word(char const *s, char c, size_t i)
{
	size_t	count;

	count = 0;
	i = 0;
	if (c != '\'' && c != '\"' )
	{
		while ((s[i] && s[i] != ' ') || (s[i] == ' ' && has_bs(s, i)))
		{
			if (has_bs(s, i))
				count++;
			++i;
		}
		return (i - count);
	}
	else
	{
		i++;
		while ((s[i] && s[i] != c) || (s[i] == c && has_bs(s, i)))
		{
			if (has_bs(s, i))
				count++;
			++i;
		}
		return (i + 1 - count);
	}
}

int	len_word_tot(char const *s, char c, size_t i)
{
	i = 0;
	if (c != '\'' && c != '\"' )
	{
		while ((s[i] && s[i] != ' ') || (s[i] == ' ' && has_bs(s, i)))
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
