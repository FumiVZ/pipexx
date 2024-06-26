/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 19:23:42 by machrist          #+#    #+#             */
/*   Updated: 2024/06/11 18:38:55 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"
#include <stdio.h>

void	close_pipes(t_pipex *pipex, t_cmd *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return ;
	if (!cmd->pipe)
		return ;
	while (i < 2 * (pipex->cmd_nmbs - 1))
	{
		if (cmd->pipe[i] != -1)
			close(cmd->pipe[i++]);
	}
}

int	wait_execve(t_pipex *pipex)
{
	int	status;
	int	i;

	i = 0;
	status = 0;
	while (i < pipex->cmd_nmbs)
	{
		waitpid(pipex->pid[i], &status, 0);
		if (WIFEXITED(status))
			pipex->env->status = status % 255;
		i++;
	}
	if (WIFEXITED(status))
		pipex->env->status = status % 255;
	return (status);
}

char	*find_path(char **env)
{
	if (!env)
		return (NULL);
	while (ft_strncmp("PATH", *env, 4))
		env++;
	if (!*env)
		return (NULL);
	return (*env + 5);
}

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		ft_printf_fd(2, "%s\n", tab[i]);
		i++;
	}
}

void	init_pipex(t_env *env)
{
	t_pipex	*pipex;

	pipex = malloc(sizeof(t_pipex));
	pipex->env = env;
	if (!pipex)
		malloc_failed(pipex);
	pipex->cmd_nmbs = 0;
	pipex->cmd = env->cmds;
	pipex->i = 0;
	pipex->pid = NULL;
	pipex->paths = ft_split(find_path(env->envp), ':');
	pipex->cmds = NULL;
	pipex->old0 = -1;
	pipex->old1 = -1;
	pipex->cmds = NULL;
	if (!pipex->paths)
		pipex->paths = ft_split("/usr/local/bin:\
			/usr/local/sbin:/usr/bin:/usr/sbin:/bin:/sbin:.", ':');
	if (!pipex->paths)
		malloc_failed(pipex);
	while (pipex->cmd[pipex->i])
		pipex->i = child_crt(pipex, env->envp);
	parent_free(pipex);
}
