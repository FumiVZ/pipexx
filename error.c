/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:38:48 by vincent           #+#    #+#             */
/*   Updated: 2024/02/18 15:19:18 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_error(char *errno_v, t_pipex *pipex, char *other)
{
	if (other)
		ft_printf(2, "pipex: %s: %s\n", other, errno_v);
	else
		ft_printf(2, "pipex: %s\n", errno_v);
	pipex->cmd[0] = NULL;
	pipex->cmd[1] = NULL;
	pipex->path = NULL;
	if (pipex->cmd[0])
		free(pipex->cmd[0]);
	else if (pipex->cmd[1])
		free(pipex->cmd[1]);
	if (pipex->path)
		free_tab(pipex->path);
/* 	if (pipex->infile)
		close(pipex->infile);
	if (pipex->outfile)
		close(pipex->outfile); */
	exit (1);
}
