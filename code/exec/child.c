/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincent <vincent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 17:28:06 by machrist          #+#    #+#             */
/*   Updated: 2024/05/05 16:11:27 by vincent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static bool	ft_builtins(t_env *env, t_pipex *pipex, char **args)
{
	if (!ft_strncmp(args[0], "echo", 5))
		ft_echo(env, args);
	else if (!ft_strncmp(args[0], "exit", 5))
		ft_exit(env, pipex);
	else if (!ft_strncmp(args[0], "cd", 3))
		ft_cd(env, args);
	else if (!ft_strncmp(args[0], "env", 4))
		ft_env(env);
	else if (!ft_strncmp(args[0], "pwd", 4))
		ft_pwd(env);
	else if (!ft_strncmp(args[0], "export", 7))
		ft_export(env, args);
	else if (!ft_strncmp(args[0], "unset", 6))
		ft_unset(env, args);
	else
		return (0);
	return (1);
}

static char	*get_cmd(char **paths, char **cmd_args)
{
	char	*tmp;
	char	*command;

	if (!paths || !cmd_args)
		return (NULL);
	if (access(cmd_args[0], X_OK) == 0 || errno == EACCES)
		return (cmd_args[0]);
	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		if (!tmp)
			return (NULL);
		command = ft_strjoin(tmp, cmd_args[0]);
		free(tmp);
		if (!command)
			return (NULL);
		if (access(command, X_OK) == 0 || errno == EACCES)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

static char	*get_cmd_with_path(t_pipex *pipex, t_cmd *cmds, char **env)
{
	if (!cmds->args)
		return (NULL);
	if (cmds->args[0][0] == '/' || !ft_strncmp(*cmds->args, "./", 2))
	{
		if (access(cmds->args[0], X_OK) == 0 || errno == EACCES)
			return (cmds->args[0]);
		ft_printf_fd(2, (char *)ERR_FILE, \
			cmds->args[0], strerror(errno));
		child_free(pipex, env);
		exit (EXIT_FAILURE);
	}
	else
		return (get_cmd(pipex->paths, cmds->args));
}

static void	child_exec(t_pipex *pipex, t_cmd *cmds, char **env)
{
	redirect(pipex, cmds);
	close_files(pipex, pipex->cmds);
	close_pipes(pipex, pipex->cmds);
	pipex->cmd_paths = get_cmd_with_path(pipex, cmds, env);
	if (!pipex->cmd_paths || errno == EACCES)
	{
		if (!ft_builtins(pipex->env, pipex, cmds->args))
		{
			if (errno == EACCES)
				msg_error_cmd(ERR_ACCESS, *cmds);
			else
				msg_error_cmd(ERR_CMD, *cmds);
			child_free(pipex, env);
			exit (EXIT_FAILURE);
		}
	}
	execve(pipex->cmd_paths, cmds->args, env);
	child_free(pipex, env);
	exit (EXIT_FAILURE);
}

int	single_command(t_pipex *pipex, t_cmd *cmds, char **env)
{
	int status;

	if (cmds->args && cmds->args[0] && !ft_strncmp(cmds->args[0], "exit", 5))
		ft_exit(pipex->env, pipex);
	pattern_matching(cmds->args, env);
	quote_removal(cmds->args);
	pipex->pid[0] = fork();
	if (pipex->pid[0] == -1)
		msg_error(ERR_FORK, pipex);
	if (pipex->pid[0] == 0 && pipex->env->status == 0)
		child_exec(pipex, cmds, env);
	close_files(pipex, pipex->cmds);
 	status = wait_execve(pipex);
	return (status);
}

int	multiple_command(t_pipex *pipex, t_cmd *cmds, char **env)
{
	int	i;

	i = 0;
	crt_pipes(pipex, cmds);
	while (cmds)
	{
		if (cmds->args && cmds->args[0] && !ft_strncmp(cmds->args[0], "exit", 5))
			ft_exit(pipex->env, pipex);
		pattern_matching(cmds->args, env);
		quote_removal(cmds->args);
		if (pipex->env->status == 0)
			pipex->pid[i] = fork();
		if (pipex->pid[i] == -1)
			msg_error(ERR_FORK, pipex);
		if (pipex->pid[i] == 0)
		{
			pipe_handle(pipex, cmds);
			child_exec(pipex, cmds, env);
		}
		cmds = cmds->next;
		i++;
	}
	close_files(pipex, pipex->cmds);
	close_pipes(pipex, pipex->cmds);
	free_split(cmds->args, ft_strstrlen(cmds->args));
	i = wait_execve(pipex);
	return (i);
}

int	child_crt(t_pipex *pipex, char **env)
{
	t_cmd	*cmds;

	pipex->env->status = 0;
	cmds = malloc(sizeof(t_cmd));
	parse_cmd(pipex, cmds);
	pipex->cmds = cmds;
	if (cmds->next && pipex->env->status == 0)
		multiple_command(pipex, cmds, env);
	else
		single_command(pipex, cmds, env);
	if (pipex->cmd[pipex->i])
		pipex->i++;
	if (pipex->env->status != 0 && pipex->cmd[pipex->i - 1] && chre(pipex->cmd[pipex->i - 1], "&&"))
		while (pipex->cmd[pipex->i] && !(chre(pipex->cmd[pipex->i], "&&") || chre(pipex->cmd[pipex->i], "||")))
			pipex->i++;
	else if (pipex->env->status == 0 && pipex->cmd[pipex->i - 1] && chre(pipex->cmd[pipex->i - 1], "||"))
		while (pipex->cmd[pipex->i] && !(chre(pipex->cmd[pipex->i], "&&") || chre(pipex->cmd[pipex->i], "||")))
			pipex->i++;
	return (pipex->i);
}
