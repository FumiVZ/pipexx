/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:13:52 by vincent           #+#    #+#             */
/*   Updated: 2024/03/16 16:52:55 by vzuccare         ###   ########lyon.fr   */
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

size_t	len_cmd(char **cmd)
{
	size_t	i;

	i = 0;
	while (cmd[i] && !is_sep(cmd[i]))
		i++;
	return (i);
}

char	**sep_case(char **cmds)
{
	size_t	j;
	size_t	len;
	char	**cmd;

	if (is_sep(*cmds) <= 4)
	{
		cmd = malloc(sizeof(char *) * 3);
		cmd[0] = ft_strdup(*cmds);
		cmd[1] = ft_strdup(*cmds + 1);
		cmd[2] = NULL;
		return (cmd);
	}
	len = len_cmd(cmds) + 1;
	cmd = malloc(sizeof(char *) * (len + 1));
	cmd[0] = ft_strdup(*cmds);
	j = 1;
	while (cmds[j] && !is_sep(cmds[j]))
	{
		cmd[j] = ft_strdup(cmds[j]);
		j++;
	}
	cmd[len] = NULL;
	return (cmd);
}

char	**create_cmd(char **cmds)
{
	size_t	j;
	size_t	len;
	char	**cmd;

	if (!cmds)
		return (NULL);
	if (!*cmds)
		return (NULL);
	if (!**cmds)
		return (NULL);
	j = 0;
	if (is_sep(cmds[j]))
		return (sep_case(cmds));
	len = len_cmd(cmds);
	cmd = malloc(sizeof(char *) * (len + 1));
	if (!cmd)
		exit(1);
	while (cmds[j] && !is_sep(cmds[j]))
	{
		cmd[j] = ft_strdup(cmds[j]);
		j++;
	}
	cmd[len] = NULL;
	return (cmd);
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
