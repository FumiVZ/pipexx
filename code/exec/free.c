/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 17:53:23 by machrist          #+#    #+#             */
/*   Updated: 2024/06/11 18:48:34 by machrist         ###   ########.fr       */
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
	// if (pipex->env->envp)
	// 	free_split(pipex->env->envp, ft_strstrlen(pipex->env->envp));
	// pipex->env->envp = NULL;
	if (pipex->env->cmds)
		free_split(pipex->env->cmds, ft_strstrlen(pipex->env->cmds));
	pipex->env->cmds = NULL;
	free(pipex);
}

void	child_free(t_pipex *pipex, char **env)
{
	(void ) env;
	close_pipes(pipex, pipex->cmds);
	close_files(pipex, pipex->cmds);
	parent_free(pipex);
	close(0);
	close(1);
}

void	malloc_failed(t_pipex *pipex)
{
	ft_printf_fd(2, "pipex: malloc failed\n");
	parent_free(pipex);
	exit (EXIT_FAILURE);
}
