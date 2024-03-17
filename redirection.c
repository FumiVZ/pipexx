/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:13:52 by vincent           #+#    #+#             */
/*   Updated: 2024/03/17 00:24:39 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_path(char **envp)
{
	size_t	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH", 4))
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

void	open_redir(t_env *env)
{
	if (is_sep(env->clean_cmds[0]) == APPEND)
		env->redir->outfile = open(env->clean_cmds[1], O_WRONLY \
			| O_APPEND | O_CREAT, 0644);
	if (is_sep(env->clean_cmds[0]) == OUT)
		env->redir->outfile = open(env->clean_cmds[1], O_WRONLY \
			| O_TRUNC | O_CREAT, 0644);
	if (is_sep(env->clean_cmds[0]) == IN)
	{
		env->redir->infile = open(env->clean_cmds[1], O_RDONLY);
		if (env->redir->infile == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(env->clean_cmds[1], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			env->status = 1;
			return ;
		}
	}
}

char	*find_cmd_path(char *cmd, char **path)
{
	char	*tmp;

	if (cmd[0] == '/' || ft_strncmp(cmd, "./", 2) == 0)
	{
		if (access(cmd, X_OK) == 0 || errno == EACCES)
			return (cmd);
		return (NULL);
	}
	tmp = ft_strdup(cmd);
	if (!tmp)
		return (NULL);
	cmd = ft_strjoin("/", tmp);
	free(tmp);
	if (!cmd)
		return (NULL);
	while (*path)
	{
		tmp = ft_strjoin(*path, cmd);
		if (access(tmp, X_OK) == 0 || errno == EACCES)
			return (free(cmd), tmp);
		free(tmp);
		path++;
	}
	return (free(cmd), NULL);
}

int	exec_cmd(t_env *env, t_redir *redir)
{
	size_t	i;

	i = 0;
	env->redir = redir;
	redir->pid = fork();
	redir->infile = 0;
	redir->outfile = 0;
	if (redir->pid == -1)
		return (1);
	if (redir->pid == 0)
	{
		if (is_sep(env->clean_cmds[0]))
		{
			redir->sep = is_sep(env->clean_cmds[0]);
			i++;
		}
		redir->args = env->clean_cmds;
		redir->paths = ft_split(find_path(env->envp), ':');
		redir->cmd_paths = find_cmd_path(env->clean_cmds[i], redir->paths);
		if (!redir->cmd_paths || errno == EACCES)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(env->clean_cmds[i], 2);
			ft_putstr_fd(": command not found\n", 2);
			ft_free_child(env);
			exit(127);
		}
		execve(redir->cmd_paths, redir->args, env->envp);
		ft_free_child(env);
		exit(126);
	}
	if (redir->infile)
		close(redir->infile);
	if (redir->outfile)
		close(redir->outfile);
	waitpid(redir->pid, &env->status, 0);
	return (0);
}
