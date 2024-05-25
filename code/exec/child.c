/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:53:07 by vzuccare          #+#    #+#             */
/*   Updated: 2024/05/25 18:43:17 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	single_command(t_pipex *pipex, t_cmd *cmds, char **env)
{
	if (cmds->exec == 1 && !is_builtin(cmds->args))
	{
		pipex->pid[0] = fork();
		if (pipex->pid[0] == -1)
			msg_error(ERR_FORK, pipex);
		if (pipex->pid[0] == 0)
			child_exec(pipex, cmds, env);
	}
	else if (cmds->exec == 1)
	{
		redirect(pipex, cmds);
		ft_builtins(pipex->env, pipex, cmds->args);
		close_files(pipex, pipex->cmds);
		if (pipex->old0 != -1 && pipex->old1 != -1)
		{
			dup2(pipex->old0, STDIN_FILENO);
			dup2(pipex->old1, STDOUT_FILENO);
		}
		pipex->pid[0] = -1;
		return ;
	}
	else
		return ;
	wait_execve(pipex);
	close_files(pipex, pipex->cmds);
}

void	execute_command(t_pipex *pipex, t_cmd *cmds, char **env, int i)
{
	pipex->pid[i] = fork();
	if (pipex->pid[i] == -1)
		msg_error(ERR_FORK, pipex);
	if (pipex->pid[i] == 0 && !is_builtin(cmds->args))
	{
		pipe_handle(pipex, cmds);
		child_exec(pipex, cmds, env);
	}
	else if (pipex->pid[i] == 0)
	{
		pipe_handle(pipex, cmds);
		redirect(pipex, cmds);
		ft_builtins(pipex->env, pipex, cmds->args);
		child_free(pipex, env);
		exit (pipex->env->status);
	}
}

void	multiple_command(t_pipex *pipex, t_cmd *cmds, char **env)
{
	int	i;

	i = 0;
	crt_pipes(pipex, cmds);
	while (cmds)
	{
		cmds->args = pattern_matching(cmds->args, env, pipex->env);
		quote_removal(cmds->args);
		if (cmds->exec == 1)
			execute_command(pipex, cmds, env, i);
		else
			pipex->pid[i] = -1;
		cmds = cmds->next;
		i++;
	}
	close_files(pipex, pipex->cmds);
	close_pipes(pipex, pipex->cmds);
	wait_execve(pipex);
}

int	child_crt(t_pipex *pipex, char **env)
{
	t_cmd	*cmds;

	cmds = malloc(sizeof(t_cmd));
	parse_cmd(pipex, cmds);
	pipex->cmds = cmds;
	if (cmds->next)
		multiple_command(pipex, cmds, env);
	else
	{
		cmds->args = pattern_matching(cmds->args, env, pipex->env);
		quote_removal(cmds->args);
		single_command(pipex, cmds, env);
	}
	if (pipex->cmd[pipex->i])
		pipex->i++;
	if (pipex->cmd[pipex->i] && !(((pipex->env->status == 0
					&& chre(pipex->cmd[pipex->i - 1], "&&")))
			|| (pipex->env->status != 0 && chre(pipex->cmd[pipex->i - 1],
					"||"))))
		while (pipex->cmd[pipex->i] && (!(chre(pipex->cmd[pipex->i], "&&"))
				|| !(chre(pipex->cmd[pipex->i], "||"))))
			pipex->i++;
	return (pipex->i);
}
