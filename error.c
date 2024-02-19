/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:38:48 by vincent           #+#    #+#             */
/*   Updated: 2024/02/19 10:38:24 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	is_cmd(char *str)
{
	if (str[0] == '-' || str[0] == '.')
		return (0);
	return (1);
}

void	ft_error(char *errno_v, t_pipex *pipex, char *other)
{
	if (other)
		ft_printf(2, "pipex: %s: %s\n", other, errno_v);
	else
		ft_printf(2, "pipex: %s\n", errno_v);
	if (pipex->cmd[0])
		free(pipex->cmd[0]);
	else if (pipex->cmd[1])
		free(pipex->cmd[1]);
	if (pipex->path)
		free_tab(pipex->path);
	if (pipex->infile)
		close(pipex->infile);
	if (pipex->outfile)
		close(pipex->outfile);
	exit (1);
}
