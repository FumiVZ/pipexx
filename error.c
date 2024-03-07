/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:38:48 by vincent           #+#    #+#             */
/*   Updated: 2024/03/07 16:45:47 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	is_cmd(char *str)
{
	if (str[0] == '-' || str[0] == '.')
		return (0);
	return (1);
}

void	ft_error(t_pipex *pipex)
{
	perror("pipex");
	if (pipex->cmd[0])
		free(pipex->cmd[0]);
	if (pipex->cmd[1])
		free(pipex->cmd[1]);
	if (pipex->args[0])
		free_tab(pipex->args[0]);
	if (pipex->args[1])
		free_tab(pipex->args[1]);
	if (pipex->path)
		free_tab(pipex->path);
	if (pipex->infile != -1)
		close(pipex->infile);
	if (pipex->outfile != -1)
		close(pipex->outfile);
	if (pipex->fd[0] != -1)
		close(pipex->fd[0]);
	if (pipex->fd[1] != -1)
		close(pipex->fd[1]);
	close(0);
	close(1);
	exit (1);
}
