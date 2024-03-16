/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:13:52 by vincent           #+#    #+#             */
/*   Updated: 2024/03/16 17:13:34 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_path(t_envp *envp)
{
	t_envp	*tmp;

	tmp = envp;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, "PATH", 4))
			return (tmp->value);
		tmp = tmp->next;
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
		env->redir->infile = open(env->clean_cmds[1], O_RDONLY);
}

char	*find_cmd_path(char *cmd, char **path)
{
	char	*tmp;

	if (cmd[0] == '/' || ft_strncmp(cmd, "./", 2) == 0)
	{
		if (access(cmd, F_OK) == 0 && access(cmd, X_OK) == 0)
			return (cmd);
		else
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
		if (access(tmp, F_OK) == 0 && access(tmp, X_OK) == 0)
			return (free(cmd), tmp);
		free(tmp);
		path++;
	}
	return (free(cmd), NULL);
}

int	exec_cmd(t_env *env)
{
	t_redir	*redir;
	size_t	i;

	i = 0;
	redir = env->redir;
	redir->pid = fork();
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
		execve(redir->cmd_paths, redir->args, NULL);
	}
	if (redir->infile)
		close(redir->infile);
	if (redir->outfile)
		close(redir->outfile);
	waitpid(redir->pid, &env->status, 0);
	return (0);
}
