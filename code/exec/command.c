/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:46:51 by vzuccare          #+#    #+#             */
/*   Updated: 2024/05/23 12:26:12 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//reproduce the behavior of pipe in bash, we need to write the output of 
//previous command to the input of the next command
//the number of pipe is equal to the number of node in the linked list

void	close_files(t_pipex	*pipex, t_cmd *cmd)
{
	int	i;

	i = -1;
	if (!cmd)
		return ;
	while (cmd)
	{
		if (cmd->infiles)
		{
			while (cmd->infiles[++i] != -1)
				close(cmd->infiles[i]);
		}
		i = -1;
		if (cmd->outfiles)
		{
			while (cmd->outfiles[++i] != -1)
				close(cmd->outfiles[i]);
		}
		cmd = cmd->next;
	}
	if (pipex->old0 != -1 && pipex->old1 != -1)
	{
		dup2(pipex->old0, STDIN_FILENO);
		dup2(pipex->old1, STDOUT_FILENO);
	}
}

void	crt_pipes(t_pipex *pipex, t_cmd *cmd)
{
	int	i;

	i = 0;
	if (pipex->cmd_nmbs < 2)
		return ;
	cmd->pipe = malloc(sizeof(int) * 2 * (pipex->cmd_nmbs - 1));
	if (!cmd->pipe)
		msg_error(ERR_PIPE, pipex);
	while (i < pipex->cmd_nmbs - 1)
	{
		if (pipe(cmd->pipe + 2 * i) == -1)
			msg_error(ERR_PIPE, pipex);
		i++;
	}
}

void	pipe_handle(t_pipex *pipex, t_cmd *cmd)
{
	if (pipex->cmd_nmbs < 2)
		return ;
	if (!pipex->cmds->pipe)
		ft_printf_fd(2, "pipe is NULL\n");
	if (cmd->pipeid == 0)
	{
		dup2(pipex->cmds->pipe[1], STDOUT_FILENO);
		close(cmd->pipe[1]);
		close(cmd->pipe[0]);
		ft_printf_fd(2, "pipeid = 0\n");
	}
	else if (cmd->pipeid == pipex->cmd_nmbs - 1)
	{
		dup2(pipex->cmds->pipe[2 * cmd->pipeid - 2], STDIN_FILENO);
		close(pipex->cmds->pipe[2 * cmd->pipeid - 2]);
		close(pipex->cmds->pipe[2 * cmd->pipeid - 1]);
	}
	else
	{
		dup2(pipex->cmds->pipe[2 * cmd->pipeid - 2], STDIN_FILENO);
		dup2(pipex->cmds->pipe[2 * cmd->pipeid + 1], STDOUT_FILENO);
		close(pipex->cmds->pipe[2 * cmd->pipeid - 2]);
		close(pipex->cmds->pipe[2 * cmd->pipeid + 1]);
	}
}

void	redirect(t_pipex *pipex, t_cmd *cmd)
{
	int		i;

	i = 0;
	pipex->old0 = dup(STDIN_FILENO);
	pipex->old1 = dup(STDOUT_FILENO);
	if (cmd->infiles)
	{
		while (cmd->infiles[i] != -1)
			i++;
		if (access(cmd->infiles_name[i - 1], R_OK) == 0)
		{
			dup2(cmd->infiles[i - 1], STDIN_FILENO);
			close(cmd->infiles[i - 1]);
		}
	}
	if (cmd->outfiles)
	{
		i = 0;
		while (cmd->outfiles[i] != -1)
			i++;
		if (access(cmd->outfiles_name[i - 1], W_OK) == 0)
		{
			dup2(cmd->outfiles[i - 1], STDOUT_FILENO);
			close(cmd->outfiles[i - 1]);
		}
	}
}

