/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_split.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 21:15:01 by machrist          #+#    #+#             */
/*   Updated: 2024/06/12 15:43:56 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parthing.h>

static	bool	check_double_special(char **str)
{
	size_t i;

	i = 0;
	while (str[i])
	{
		if (is_special_no_par(str[i][0]))
		{
			if (!str[i + 1])
				return (msg_err(ERR_TOKEN));
			else if (is_special_no_par(str[i + 1][0]))
				return (msg_err(ERR_TOKEN));
		}
		i++;
	}
	return (true);
}

bool	check_syntax_split(char **str)
{
	if (!str)
		return (true);
	if (!check_double_special(str))
		return (false);
	return (true);
}
