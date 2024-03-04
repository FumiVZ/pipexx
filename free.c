/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:03:36 by vzuccare          #+#    #+#             */
/*   Updated: 2024/03/04 13:26:56 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_child(t_pipex *pipex)
{
	close(0);
	close(1);
	if (pipex->cmd[0])
		free(pipex->cmd[0]);
	if (pipex->args[0])
		free_tab(pipex->args[0]);
	free_tab(pipex->path);
}

void	free_child2(t_pipex *pipex)
{
	free_child(pipex);
	if (pipex->fd[0] != -1)
		close(pipex->fd[0]);
	if (pipex->fd[1] != -1)
		close(pipex->fd[1]);
	if (pipex->infile != -1)
		close(pipex->infile);
	if (pipex->outfile != -1)
		close(pipex->outfile);
	if (pipex->cmd[1])
		free(pipex->cmd[1]);
	if (pipex->args[1])
		free_tab(pipex->args[1]);
}
