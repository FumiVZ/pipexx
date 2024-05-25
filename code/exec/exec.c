/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 17:28:06 by machrist          #+#    #+#             */
/*   Updated: 2024/05/25 14:28:26 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	ft_builtins(t_env *env, t_pipex *pipex, char **args)
{
	if (!args || !args[0])
		return (0);
	if (!ft_strncmp(args[0], "echo", 5))
		ft_echo(env, args);
	else if (!ft_strncmp(args[0], "exit", 5))
		ft_exit(env, pipex, args);
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

int	is_builtin(char **args)
{
	if (!args || !args[0])
		return (0);
	if (!ft_strncmp(args[0], "echo", 5))
		return (1);
	else if (!ft_strncmp(args[0], "exit", 5))
		return (1);
	else if (!ft_strncmp(args[0], "cd", 3))
		return (1);
	else if (!ft_strncmp(args[0], "env", 4))
		return (1);
	else if (!ft_strncmp(args[0], "pwd", 4))
		return (1);
	else if (!ft_strncmp(args[0], "export", 7))
		return (1);
	else if (!ft_strncmp(args[0], "unset", 6))
		return (1);
	else
		return (0);
}

static int	is_dir(const char *path, t_pipex *pipex)
{
	struct stat	statbuf;

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
		if (is_dir(command, pipex))
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
		if (access(cmds->args[0], X_OK) == 0 || errno == EACCES)
			return (cmds->args[0]);
		if (is_dir(cmds->args[0], pipex))
			return (cmds->args[0]);
		ft_printf_fd(2, (char *)ERR_FILE, cmds->args[0], strerror(errno));
		child_free(pipex, env);
		exit(127);
	}
	else
		return (get_cmd(pipex->paths, cmds->args, pipex));
}

void	child_exec(t_pipex *pipex, t_cmd *cmds, char **env)
{
	redirect(pipex, cmds);
	close_files(pipex, pipex->cmds);
	close_pipes(pipex, pipex->cmds);
	if (!cmds->args || !cmds->args[0])
	{
		child_free(pipex, env);
		exit(0);
	}
	pipex->cmd_paths = get_cmd_with_path(pipex, cmds, env);
	if (!pipex->cmd_paths || errno == EACCES || pipex->is_dir)
	{
		if (pipex->is_dir)
		{
			if (errno == EACCES)
				msg_error_cmd(ERR_ACCESS, *cmds);
			else
				msg_error_cmd(ERR_IS_DIR, *cmds);
			child_free(pipex, env);
			exit(126);
		}
		if (errno == EACCES)
		{
			msg_error_cmd(ERR_ACCESS, *cmds);
			child_free(pipex, env);
			exit(127);
		}
		else
			msg_error_cmd(ERR_CMD, *cmds);
		child_free(pipex, env);
		exit(127);
	}
	execve(pipex->cmd_paths, cmds->args, env);
	child_free(pipex, env);
	exit(12);
}
