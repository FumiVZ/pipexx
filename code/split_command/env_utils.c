/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 05:55:14 by machrist          #+#    #+#             */
/*   Updated: 2024/05/22 20:33:29 by machrist         ###   ########.fr       */
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

char	**clean_str(char **str, size_t pos)
{
	size_t	i;
	size_t	j;
	char	**new_str;

	new_str = malloc(sizeof(char *) * (ft_strstrlen(str)));
	if (!new_str)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (i != pos)
			new_str[j++] = str[i];
		else
			free(str[i]);
		i++;
	}
	new_str[j] = NULL;
	free(str);
	return (new_str);
}

char	**check_str(char **str, size_t *pos)
{
	size_t	i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (!str[i][0])
		{
			str = clean_str(str, i);
			if (!str)
				return (NULL);
			*pos -= 1;
			return (str);
		}
		i++;
	}
	return (str);
}
