/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:47:09 by machrist          #+#    #+#             */
/*   Updated: 2024/03/16 21:15:15 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_free_child(t_env *env)
{
	free_split(env->envp, ft_strstrlen(env->envp));
	free_split(env->cmds, ft_strstrlen(env->cmds));
	free_split(env->clean_cmds, ft_strstrlen(env->clean_cmds));
	free_split(env->redir->paths, ft_strstrlen(env->redir->paths));
	free(env->redir->cmd_paths);
}

void	ft_free_parent(t_env *env)
{
	free_split(env->envp, ft_strstrlen(env->envp));
}
