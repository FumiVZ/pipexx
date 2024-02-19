/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 10:21:20 by vzuccare          #+#    #+#             */
/*   Updated: 2024/02/19 12:18:55 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex_init(t_pipex *pipex)
{
	pipex->cmd[0] = NULL;
	pipex->cmd[1] = NULL;
	pipex->path = NULL;
	pipex->args[0] = NULL;
	pipex->args[1] = NULL;
	pipex->infile = 0;
	pipex->outfile = 0;
	pipex->fd[0] = 0;
	pipex->fd[1] = 0;
	pipex->pid1 = 0;
	pipex->pid2 = 0;
}

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

char	*current_directory(char *cmd)
{
	char	*tmp;

	tmp = first_word(cmd);
	tmp = ft_strjoin_free("./", tmp);
	if (!tmp)
	{
		free(cmd);
		ft_error(strerror(errno), NULL, NULL);
	}
	if (access(tmp, X_OK) == 0 && access(tmp, F_OK) == 0)
	{
		free(cmd);
		return (tmp);
	}
	if (access(cmd, X_OK) != 0 && access(cmd, F_OK) == 0)
	{
		free(tmp);
		return (ft_strdup("/"));
	}
	free(tmp);
	return (NULL);
}

char	*get_cmd_path(char **path, char *cmd)
{
	char	*tmp;

	if (!cmd)
		return (NULL);
	tmp = NULL;
	tmp = current_directory(cmd);
	if (tmp)
		return (current_directory(cmd));
	tmp = NULL;
	free(tmp);
	cmd = ft_strjoin_free("/", cmd);
	if (!cmd)
		return (NULL);
	while (*path)
	{
		tmp = ft_strjoin(*path, cmd);
		if (access(tmp, X_OK) == 0)
			return (free(cmd), tmp);
		free(tmp);
		path++;
	}
	return (free(cmd), ft_strdup("/"));
}
