/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:13:52 by vincent           #+#    #+#             */
/*   Updated: 2024/03/16 15:00:58 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
