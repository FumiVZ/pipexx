/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 10:21:20 by vzuccare          #+#    #+#             */
/*   Updated: 2024/03/07 17:40:38 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_tab(char **tab)
{
	ssize_t	i;

	if (!tab)
		return ;
	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

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

void	init_exec(t_pipex *pipex, char **av, int i)
{
	int	j;

	if (i == 0)
		j = 2;
	else
		j = 3;
	pipex->cmd[i] = get_cmd_path(pipex->path, first_word(av[j]));
	if (pipex->cmd[i] == NULL)
		return ;
	pipex->args[i] = ft_split(av[j], ' ');
	if (pipex->args[i] == NULL)
		ft_error(pipex);
}

char	*get_env_path(char **env)
{
	ssize_t	i;
	char	*default_path;

	default_path = "/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin";
	i = -1;
	while (env[++i])
		if (!ft_strncmp(env[i], "PATH=", 5))
			return (env[i] + 5);
	return (default_path);
}

char	*get_cmd_path(char **path, char *cmd)
{
	char	*tmp;

	if (!cmd)
		return (NULL);
	tmp = NULL;
	if (cmd[0] == '/' || ft_strncmp(cmd, "./", 2) == 0)
	{
		if (access(cmd, X_OK) == 0)
			return (cmd);
		else
			return (free(cmd), NULL);
	}
	cmd = ft_strjoin_free("/", cmd);
	if (!cmd)
		return (NULL);
	while (*path)
	{
		tmp = ft_strjoin(*path, cmd);
		if (access(tmp, F_OK) == 0 && access(tmp, X_OK) == 0)
			return (free(cmd), tmp);
		free(tmp);
		path++;
	}
	return (free(cmd), NULL);
}
