/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:53:07 by vzuccare          #+#    #+#             */
/*   Updated: 2024/06/13 16:41:42 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	single_command(t_pipex *pipex, t_cmd *cmds, char **env)
{
 	// set_last_param(pipex->env, cmds->args[ft_strstrlen(cmds->args) - 1]);
	// if (!pipex->env->envp)
	// {
	// 	parent_free(pipex);
	// 	exit (1);
	// }
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
		if (pipex->old0 != -1 && pipex->old1 != -1)
		{
			secure_dup2(pipex->old0, STDIN_FILENO, pipex);
			secure_dup2(pipex->old1, STDOUT_FILENO, pipex);
		}
		close_files(pipex, pipex->cmds);
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
	int	status;

 	// set_last_param(pipex->env, cmds->args[ft_strstrlen(cmds->args) - 1]);
	// if (!pipex->env->envp)
	// {
	// 	parent_free(pipex);
	// 	exit (1);
	// }
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
		status = pipex->env->status;
		free_split(pipex->env->envp, ft_strstrlen(pipex->env->envp));
		child_free(pipex, env);
		exit (status);
	}
}

void	multiple_command(t_pipex *pipex, t_cmd *cmds, char **env)
{
	int		i;
	t_cmd	*tmp;

	i = 0;
	crt_pipes(pipex, cmds);
	while (cmds)
	{
		cmds->args = pattern_matching(cmds->args, env, pipex->env);
		quote_removal(cmds->args);
		if (!cmds->args)
			msg_error(ERR_MALLOC, pipex);
		if (cmds->exec == 1)
			execute_command(pipex, cmds, env, i);
		else
			pipex->pid[i] = -1;
		tmp = cmds;
		cmds = cmds->next;
		i++;
	}
	close_files(pipex, pipex->cmds);
	close_pipes(pipex, pipex->cmds);
	wait_execve(pipex);
	if (tmp->exec == 0)
		pipex->env->status = 1;
}

int	child_crt(t_pipex *pipex, char **env)
{
	t_cmd	*cmds;

	cmds = malloc(sizeof(t_cmd));
	pipex->cmds = cmds;
	parse_cmd(pipex, cmds);
	if (cmds->next)
		multiple_command(pipex, cmds, env);
	else
	{
		cmds->args = pattern_matching(cmds->args, env, pipex->env);
		quote_removal(cmds->args);
		if (!cmds->args)
			msg_error(ERR_MALLOC, pipex);
		single_command(pipex, cmds, env);
	}
	if (pipex->cmd[pipex->i] && !(((pipex->env->status == 0
					&& ft_strncmp(pipex->cmd[pipex->i - 1], "&&", 2) == 0))
			|| (pipex->env->status != 0 && ft_strncmp(pipex->cmd[pipex->i - 1],
					"||", 2) == 0)))
		while (pipex->cmd[pipex->i] && \
			(!(ft_strncmp(pipex->cmd[pipex->i], "&&", 2) == 0)
				|| !(ft_strncmp(pipex->cmd[pipex->i], "||", 2) == 0)))
			pipex->i++;
	return (pipex->i);
}
