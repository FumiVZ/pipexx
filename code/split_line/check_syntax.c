/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 18:42:59 by machrist          #+#    #+#             */
/*   Updated: 2024/04/24 22:28:49 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parthing.h>

static bool	is_special_no_par(char c)
{
	return (c == '|' || c == '&' || c == '<' || c == '>');
}

static void	check_quote(char c, bool *quote, bool *dquote)
{
	if (c == '\'' && !*dquote)
		*quote = !*quote;
	if (c == '\"' && !*quote)
		*dquote = !*dquote;
}

static bool	check_par(char *str, bool quote, bool dquote)
{
	size_t	i;
	size_t	nb_par_open;
	size_t	nb_par_close;

	i = 0;
	nb_par_close = 0;
	nb_par_open = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '(' && !quote && !dquote)
			return (false);
		if (str[i] == '(' && !quote && !dquote)
			nb_par_open++;
		if (str[i] == ')' && !quote && !dquote)
			nb_par_close++;
		check_quote(str[i], &quote, &dquote);
		if (nb_par_close > nb_par_open)
			return (false);
		i++;
	}
	if (nb_par_close != nb_par_open)
		return (false);
	return (true);
}

static bool	check_special(char *str, bool quote, bool dquote)
{
	size_t	i;

	if (str[0] == '|' || str[0] == '&')
		return (false);
	i = 0;
	while (str[i])
	{
		if (is_special_no_par(str[i]) && !quote && !dquote)
		{
			if (str[i] == '&' && str[i + 1] != '&')
				return (false);
			if (is_special_no_par(str[i + 1]))
				if (str[i] != str[i + 1] || is_special_no_par(str[i + 2]))
					return (false);
		}
		check_quote(str[i], &quote, &dquote);
		i++;
	}
	if (is_special_no_par(str[i - 1]) && !quote && !dquote)
		return (false);
	return (true);
}

bool	check_syntax(char *str)
{
	bool	quote;
	bool	dquote;

	quote = false;
	dquote = false;
	if (!check_par(str, quote, dquote))
		return (false);
	if (!check_special(str, quote, dquote))
		return (false);
	return (true);
}
