/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 17:53:23 by machrist          #+#    #+#             */
/*   Updated: 2024/05/21 17:30:20 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/child.h"

void	parent_free(t_pipex *pipex)
{
	int	i;

	if (!pipex)
		return ;
	if (pipex->paths)
	{
		i = 0;
		while (pipex->paths[i])
			free(pipex->paths[i++]);
		free(pipex->paths);
	}
	if (pipex->cmds)
		free_l(pipex->cmds);
	if (pipex->pid)
		free(pipex->pid);
	pipex->cmds = NULL;
	if (pipex->env->cmds)
		free_split(pipex->env->cmds, ft_strstrlen(pipex->env->cmds));
	free(pipex);
}

void	child_free(t_pipex *pipex, char **env)
{
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
