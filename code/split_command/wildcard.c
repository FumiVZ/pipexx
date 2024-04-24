/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:57:00 by machrist          #+#    #+#             */
/*   Updated: 2024/04/24 18:29:05 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parthing.h"

static bool	check_is_dir(const char *dir)
{
	char		*pwd;
	char		*path;
	struct stat	info;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (msg_err(GETCWD));
	path = ft_strjoin(pwd, "/");
	free(pwd);
	if (!path)
		return (msg_err(MALLOC));
	pwd = ft_strjoin(path, dir);
	free(path);
	if (!pwd)
		return (msg_err(MALLOC));
	if (stat(pwd, &info) != 0)
	{
		free(pwd);
		return (msg_err(STAT));
	}
	free(pwd);
	if (S_ISDIR(info.st_mode))
		return (true);
	return (false);
}

static bool	match(const char *str, const char *pattern, const char *dir)
{
	const char	*next_pattern;

	if (str[0] == '.' && pattern[0] != '.')
		return (0);
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
				if (match(str++, next_pattern, dir))
					return (1);
			return (0);
		}
		else if (*pattern != '?' && *str != *pattern)
		{
			while (*pattern == '/')
			{
				pattern++;
				if (*pattern == '\0' && check_is_dir(dir))
					return (1);
			}
			return (0);
		}
		str++;
		pattern++;
	}
	while (*pattern == '*')
		pattern++;
	if (*pattern == '\0' && *str == '\0')
		return (1);
	return (*str == '\0' && *pattern == '\0');
}

static char	*add_back(char *result, const char *d_name)
{
	char	*tmp;
	size_t	len;

	len = ft_strlen(result) + ft_strlen(d_name) + 2;
	tmp = malloc(sizeof(char *) * len);
	if (!tmp)
		return (free(result), NULL);
	ft_strlcpy(tmp, result, ft_strlen(result) + 1);
	ft_strlcat(tmp, " ", ft_strlen(result) + 2);
	ft_strlcat(tmp, d_name, ft_strlen(result) + ft_strlen(d_name) + 2);
	free(result);
	return (tmp);
}

static bool	set_result(char **result, const struct dirent *entry, const char *pattern)
{
	const char	*tmp;

	if (pattern[ft_strlen(pattern) - 1] == '/')
		tmp = ft_strjoin(entry->d_name, "/");
	else
		tmp = entry->d_name;
	if (*result != NULL)
	{
		*result = add_back(*result, tmp);
		if (pattern[ft_strlen(pattern) - 1] == '/')
			free((char *)tmp);
		if (!*result)
			return (msg_err(MALLOC));
	}
	else
	{
		*result = ft_strdup(tmp);
		if (pattern[ft_strlen(pattern) - 1] == '/')
			free((char *)tmp);
		if (!*result)
			return (msg_err(MALLOC));
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
		if (match(entry->d_name, pattern, entry->d_name))
			if (!set_result(&result, entry, pattern))
			{
				closedir(dir);
				return (NULL);
			}
		entry = readdir(dir);
	}
	if (!result)
	{
		closedir(dir);
		return (ft_strdup(""));
	}
	closedir(dir);
	result = sort_result(result);
	if (!result)
		return (NULL);
	return (result);
}
