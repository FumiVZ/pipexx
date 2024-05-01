/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincent <vincent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 17:51:11 by machrist          #+#    #+#             */
/*   Updated: 2024/05/01 19:35:57 by vincent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/error.h"

int	msg(char *err)
{
	ft_printf_fd(2, err);
	return (EXIT_FAILURE);
}

void	msg_error_cmd(char *err, t_cmd cmds)
{
	if (ft_strncmp(err, ERR_CMD, 10) == 0)
	{
		if (!cmds.args)
			ft_printf_fd(2, "%s", (char *)ERR_CMD_EMPTY);
		else if (!cmds.args[0])
			ft_printf_fd(2, "%s", (char *)ERR_CMD_EMPTY);
		else
			ft_printf_fd(2, err, cmds.args[0]);
	}
	else
	{
		if (!cmds.args)
			ft_printf_fd(2, "%s", (char *)ERR_ACCESS_EMPTY);
		else if (!cmds.args[0])
			ft_printf_fd(2, "%s", (char *)ERR_ACCESS_EMPTY);
		else
			ft_printf_fd(2, err, cmds.args[0]);
	}
}

void	msg_error_infile(char *err, t_pipex pipex, t_cmd cmds)
{
	if (!cmds.infiles_name)
		perror("pipex");
	else
		ft_printf_fd(2, err, cmds.infiles_name, strerror(errno));
	pipex.env->status = EXIT_FAILURE;
}

void	msg_error_outfile(char *err, t_pipex pipex, t_cmd cmds)
{
	if (!cmds.outfiles_name)
		perror("pipex");
	else
		ft_printf_fd(2, err, cmds.outfiles_name, strerror(errno));
	pipex.env->status = EXIT_FAILURE;
}

void	msg_error(char *err, t_pipex *pipex)
{
	perror(err);
	parent_free(pipex);
	exit (EXIT_FAILURE);
}
