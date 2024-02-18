/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 10:21:20 by vzuccare          #+#    #+#             */
/*   Updated: 2024/02/18 14:25:18 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_tab(char **tab)
{
	size_t	i;

	i = -1;
	while (tab[++i])
		printf("%s\n", tab[i]);
}

char	*get_env_path(char **env)
{
	size_t	i;
	char	*default_path;

	default_path = "/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin";
	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
			return (env[i] + 5);
	}
	return (default_path);
}

char	*get_cmd_path(char **path, char *cmd)
{
	char	*tmp;

	if (!path || !cmd)
		return (free(cmd), NULL);
	if (access(cmd, X_OK) == 0)
	{
		tmp = first_word(cmd);
		if (!tmp)
			return (free(cmd), NULL);
		free(cmd);
		return (tmp);
	}
	cmd = ft_strjoin_free("/", cmd);
	if (!cmd)
		return (NULL);
	while (*path)
	{
		tmp = ft_strjoin(*path, cmd);
		if (access(tmp, X_OK) == 0 || errno == EACCES)
			return (free(cmd), tmp);
		free(tmp);
		path++;
	}
	return (free(cmd), NULL);
}
