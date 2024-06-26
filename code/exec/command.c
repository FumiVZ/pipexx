/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:46:51 by vzuccare          #+#    #+#             */
/*   Updated: 2024/06/12 18:42:23 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//reproduce the behavior of pipe in bash, we need to write the output of 
//previous command to the input of the next command
//the number of pipe is equal to the number of node in the linked list

void	backup_fd(t_pipex *pipex)
{
	pipex->old0 = dup(STDIN_FILENO);
	pipex->old1 = dup(STDOUT_FILENO);
}

void	close_files(t_pipex	*pipex, t_cmd *cmd)
{
	int	i;

	if (!cmd)
		return ;
	if (pipex->old0 != -1 || pipex->old1 != -1)
		close_reset(pipex->old0, pipex->old1);
	while (cmd)
	{
		i = -1;
		if (cmd->infiles)
		{
			while (cmd->infiles_name[++i])
				close(cmd->infiles[i]);
		}	
		i = -1;
		if (cmd->outfiles)
			while (cmd->outfiles_name[++i])
				close(cmd->outfiles[i]);
		cmd = cmd->next;
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
	if (cmd->id == 0)
	{
		secure_dup2(pipex->cmds->pipe[1], STDOUT_FILENO, pipex);
		close(cmd->pipe[1]);
		close(cmd->pipe[0]);
	}
	else if (cmd->id == pipex->cmd_nmbs - 1)
	{
		secure_dup2(pipex->cmds->pipe[2 * cmd->id - 2], STDIN_FILENO, pipex);
		close(pipex->cmds->pipe[2 * cmd->id - 2]);
		close(pipex->cmds->pipe[2 * cmd->id - 1]);
	}
	else
	{
		secure_dup2(pipex->cmds->pipe[2 * cmd->id - 2], STDIN_FILENO, pipex);
		secure_dup2(pipex->cmds->pipe[2 * cmd->id + 1], STDOUT_FILENO, pipex);
		close(pipex->cmds->pipe[2 * cmd->id - 2]);
		close(pipex->cmds->pipe[2 * cmd->id + 1]);
	}
}

void	redirect(t_pipex *pipex, t_cmd *cmd)
{
	int		i;

	i = 0;
	backup_fd(pipex);
	if (cmd->infiles)
	{
		while (cmd->infiles[i] != -1)
			i++;
		if (access(cmd->infiles_name[i - 1], R_OK) == 0)
		{
			secure_dup2(cmd->infiles[i - 1], STDIN_FILENO, pipex);
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
			secure_dup2(cmd->outfiles[i - 1], STDOUT_FILENO, pipex);
			close(cmd->outfiles[i - 1]);
		}
	}
}
