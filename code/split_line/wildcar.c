/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:57:00 by machrist          #+#    #+#             */
/*   Updated: 2024/03/16 14:50:32 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parthing.h"

static int	match(const char *str, const char *pattern)
{
	const char	*next_pattern;

	next_pattern = pattern + 1;
	while (*str && *pattern)
	{
		if (*pattern == '*')
		{
			while (*next_pattern == '*')
				next_pattern++;
			if (*next_pattern == '\0')
				return (1);
			while (*str)
				if (match(str++, next_pattern))
					return (1);
			return (0);
		}
		else if (*pattern != '?' && *str != *pattern)
			return (0);
		str++;
		pattern++;
	}
	return (*str == '\0' && *pattern == '\0');
}

static char	*add_back(char *result, const char *d_name)
{
	char	*tmp;

	tmp = malloc(ft_strlen(result) + ft_strlen(d_name) + 2);
	if (!tmp)
		return (free(result), NULL);
	ft_strlcpy(tmp, result, ft_strlen(result) + 1);
	ft_strlcat(tmp, " ", ft_strlen(result) + 2);
	ft_strlcat(tmp, d_name, ft_strlen(result) + ft_strlen(d_name) + 2);
	free(result);
	return (tmp);
}

static bool	set_result(char **result, const struct dirent *entry)
{
	if (*result != NULL)
	{
		*result = add_back(*result, entry->d_name);
		if (!*result)
			return (perror("malloc"), false);
	}
	else
	{
		*result = ft_strdup(entry->d_name);
		if (!*result)
			return (perror("malloc"), false);
	}
	return (true);
}

char	*wildcard_match(const char *pattern)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*result;

	result = NULL;
	dir = opendir(".");
	if (!dir)
		return (perror("opendir"), NULL);
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (ft_strncmp(entry->d_name, ".", 2) && ft_strncmp(entry->d_name, "..",
				3))
			if (match(entry->d_name, pattern))
				if (!set_result(&result, entry))
					return (closedir(dir), NULL);
		entry = readdir(dir);
	}
	if (!result)
	{
		closedir(dir);
		return (ft_strdup(""));
	}
	return (closedir(dir), result);
}
