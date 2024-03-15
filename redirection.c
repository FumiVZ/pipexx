/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincent <vincent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:13:52 by vincent           #+#    #+#             */
/*   Updated: 2024/03/15 19:26:17 by vincent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_redir(t_env *env)
{	
	env->redir = malloc(sizeof(t_redir));
	if (!env->redir)
		exit(1);
	env->redir->cmd = NULL;
	env->redir->prev_pid = -1;
	env->redir->sep = 0;
	env->redir->fd_in = 0;
	env->redir->fd_out = 1;
	env->redir->paths = NULL;
}

char	*find_path(t_envp *envp)
{
	while (envp)
	{
		if (!ft_strncmp(envp->name, "PATH", 4))
			return (envp->value);
		envp = envp->next;
	}
	return (NULL);
}

/* void	redirection(t_env *env)
{
	t_redir	*redir;

	redir = env->redir;
	redir->cmd_paths = ft_split(redir->cmd, ':');
	
} */

size_t	len_cmd(char **cmd)
{
	size_t	i;

	i = 0;
	while (cmd[i] && !is_sep(cmd[i]))
		i++;
	printf("len = %ld\n", i);
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
		return(NULL);
	if (!*cmds)
		return (NULL);
	if (!**cmds)
		return(NULL);
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
