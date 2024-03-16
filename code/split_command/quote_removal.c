/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:14:22 by machrist          #+#    #+#             */
/*   Updated: 2024/03/16 17:50:37 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parthing.h>

static size_t	len_word(char *str)
{
	size_t	i;
	size_t	len;
	bool	quote;
	bool	dquote;

	i = 0;
	len = 0;
	quote = false;
	dquote = false;
	while (str[i])
	{
		if (str[i] == '\'' && !dquote)
			quote = !quote;
		if (str[i] == '\"' && !quote)
			dquote = !dquote;
		if (str[i] == '\'' || str[i] == '\"')
			i++;
		if (str[i])
		{
			len++;
			i++;
		}
	}
	return (len);
}

static bool	check_quote(char *str, size_t *i, bool *quote, bool *dquote)
{
	if (str[*i] == '\'' && !*dquote)
	{
		*quote = !*quote;
		(*i)++;
		return (true);
	}
	if (str[*i] == '\"' && !*quote)
	{
		*dquote = !*dquote;
		(*i)++;
		return (true);
	}
	return (false);
}

static char	*quote_removal_world(char *str, char *tmp)
{
	size_t	j;
	size_t	pos;
	size_t	len;
	bool	quote;
	bool	dquote;

	len = len_word(str);
	tmp = malloc(len + 1);
	if (!tmp)
		return (NULL);
	quote = false;
	dquote = false;
	j = 0;
	pos = 0;
	while (str[j])
	{
		while (str[j] && check_quote(str, &j, &quote, &dquote))
			;
		tmp[pos++] = str[j];
		if (str[j])
			j++;
	}
	tmp[len] = '\0';
	return (tmp);
}

void	quote_removal(char **str)
{
	size_t	i;
	char	*tmp;

	i = 0;
	while (str[i])
	{
		if (ft_strlen(str[i]) != len_word(str[i]))
		{
			tmp = quote_removal_world(str[i], tmp);
			free(str[i]);
			str[i] = tmp;
		}
		i++;
	}
}
