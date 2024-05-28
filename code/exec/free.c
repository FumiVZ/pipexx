/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 17:53:23 by machrist          #+#    #+#             */
/*   Updated: 2024/05/28 14:37:09 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../header/child.h"

void	parent_free(t_pipex *pipex)
{
	int	i;

	if (!pipex)
		return ;
	if (pipex->old0 != -1 || pipex->old1 != -1)
		close_reset(pipex->old0, pipex->old1);
	if (pipex->paths)
	{
		i = 0;
		while (pipex->paths[i])
			free(pipex->paths[i++]);
		free(pipex->paths);
	}
	if (pipex->cmds)
		free_l(pipex->cmds);
	pipex->cmds = NULL;
	if (pipex->pid)
		free(pipex->pid);
	if (pipex->env->cmds)
		free_split(pipex->env->cmds, ft_strstrlen(pipex->env->cmds));
	free(pipex);
}

void	child_free(t_pipex *pipex, char **env)
{
	close_pipes(pipex, pipex->cmds);
	close_files(pipex, pipex->cmds);
	parent_free(pipex);
	free_split(env, ft_strstrlen(env));
	close(0);
	close(1);
}

void	malloc_failed(t_pipex *pipex)
{
	ft_printf_fd(2, "pipex: malloc failed\n");
	parent_free(pipex);
	exit (EXIT_FAILURE);
}
