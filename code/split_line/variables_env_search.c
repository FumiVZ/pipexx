/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_env_search.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 13:31:29 by machrist          #+#    #+#             */
/*   Updated: 2024/03/17 15:17:17 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parthing.h"

static bool	is_valid_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

size_t	get_len_name(char *str)
{
	size_t	len;

	if (str[0] == '?')
		return (1);
	len = 0;
	while (str[len] && is_valid_char(str[len]))
		len++;
	return (len);
}

char	*get_value(char *str, char **env)
{
	size_t	i;
	size_t	len;
	char	*value;

	i = 0;
	if (str[0] == '?')
		return (ft_itoa(0));
	while (env[i])
	{
		if (!ft_strncmp(env[i], str, get_len_name(str)))
		{
			if (env[i][get_len_name(str)] == '=')
			{
				len = ft_strlen(env[i]) - get_len_name(str) - 1;
				value = malloc(len + 1);
				if (!value)
					return (NULL);
				ft_strlcpy(value, env[i] + get_len_name(str) + 1, len + 1);
				return (value);
			}
		}
		i++;
	}
	return (ft_strdup(""));
}

char	*new_str(char *str, char *value, size_t len)
{
	char	*new;
	size_t	i;
	size_t	j;

	if (!value)
		return (NULL);
	new = malloc(ft_strlen(str) - len + ft_strlen(value) + 1);
	if (!new)
		return (free(value), NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$' && get_len_name(str + i + 1) == len)
		{
			ft_strlcpy(new + i, value, ft_strlen(value) + 1);
			j += ft_strlen(value);
			i += len + 1;
		}
		else
			new[j++] = str[i++];
	}
	new[j] = '\0';
	free(value);
	return (new);
}
