/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 17:28:06 by machrist          #+#    #+#             */
/*   Updated: 2024/06/12 17:37:20 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	is_dir(const char *path, t_pipex *pipex)
{
	struct stat	statbuf;

	if (!path)
		return (false);
	if (stat(path, &statbuf) != 0)
	{
		pipex->is_dir = false;
		return (false);
	}
	if (S_ISDIR(statbuf.st_mode))
		pipex->is_dir = true;
	else
		pipex->is_dir = false;
	return (pipex->is_dir);
}

static char	*get_cmd(char **paths, char **cmd_args, t_pipex *pipex)
{
	char	*tmp;
	char	*command;

	(void) pipex;
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
/* 		if (is_dir(command, pipex))
			return (command); */
		if (access(command, X_OK) == 0 || errno == EACCES)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

static char	*get_cmd_with_path(t_pipex *pipex, t_cmd *cmds, char **env)
{
	if (cmds->args[0][0] == '/' || !ft_strncmp(*cmds->args, "./", 2))
	{
		if (is_dir(cmds->args[0], pipex))
			return (cmds->args[0]);
		if (access(cmds->args[0], X_OK) == 0 || errno == EACCES)
			return (cmds->args[0]);
		ft_printf_fd(2, (char *)ERR_FILE, cmds->args[0], strerror(errno));
		free_split(pipex->env->envp, ft_strstrlen(pipex->env->envp));
		child_free(pipex, env);
		exit(127);
	}
	else
		return (get_cmd(pipex->paths, cmds->args, pipex));
}

static void	exec_error(t_pipex *pipex, t_cmd *cmds, char **env)
{
	if ((pipex->is_dir && (cmds->args[0][0] == '/' || !ft_strncmp(*cmds->args,
				"./", 2))) || errno == EACCES)
	{
		if (errno == EACCES)
			msg_error_cmd(ERR_ACCESS, *cmds);
		else
			msg_error_cmd(ERR_IS_DIR, *cmds);
		child_free(pipex, env);
		exit(126);
	}
	else
		msg_error_cmd(ERR_CMD, *cmds);
}

void	child_exec(t_pipex *pipex, t_cmd *cmds, char **env)
{
	pipex->is_dir = false;
	redirect(pipex, cmds);
	close_files(pipex, pipex->cmds);
	close_pipes(pipex, pipex->cmds);
	if (!cmds->args || !cmds->args[0])
	{
		free_split(pipex->env->envp, ft_strstrlen(pipex->env->envp));
		child_free(pipex, env);
		exit(0);
	}
	pipex->cmd_paths = get_cmd_with_path(pipex, cmds, env);
	if (!pipex->cmd_paths || errno == EACCES || pipex->is_dir)
	{
		exec_error(pipex, cmds, env);
		free_split(pipex->env->envp, ft_strstrlen(pipex->env->envp));
		child_free(pipex, env);
		exit(127);
	}
	execve(pipex->cmd_paths, cmds->args, env);
	free_split(pipex->env->envp, ft_strstrlen(pipex->env->envp));
	child_free(pipex, env);
	exit(EXIT_FAILURE);
}
