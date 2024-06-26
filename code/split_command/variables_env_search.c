/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_env_search.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 13:31:29 by machrist          #+#    #+#             */
/*   Updated: 2024/05/27 22:11:43 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parthing.h"

char	*ifs_value(char **env)
{
	size_t	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "IFS=", 4))
			return (env[i] + 4);
		i++;
	}
	return (" \t\n");
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

char	*get_value(char *str, char **env, t_env *envp)
{
	size_t	i;
	size_t	len;
	char	*value;

	i = 0;
	if (str[0] == '?')
		return (ft_itoa(envp->status));
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

char	*add_var_env(char *str, char *value, size_t len, size_t pos)
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
		if (i == pos - 1)
		{
			ft_strlcpy(new + i, value, ft_strlen(value) + 1);
			j += ft_strlen(value);
			i += len;
		}
		else
			new[j++] = str[i++];
	}
	new[j] = '\0';
	free(value);
	return (new);
}

char	*full_str(char *str, char *value, size_t pos)
{
	char	*new;
	size_t	i;
	size_t	j;

	new = malloc(ft_strlen(str) + ft_strlen(value) - get_len_name(str + pos));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (i == pos - 1)
		{
			ft_strlcpy(new + j, value, ft_strlen(value) + 1);
			j += ft_strlen(value);
			i += get_len_name(str + pos) + 1;
		}
		else
			new[j++] = str[i++];
	}
	new[j] = '\0';
	free(value);
	return (new);
}
