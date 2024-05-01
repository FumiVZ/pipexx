/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincent <vincent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:46:38 by machrist          #+#    #+#             */
/*   Updated: 2024/05/01 17:11:53 by vincent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <pipex.h>
#include <struct.h>
#include <error.h>

void	ft_exit(t_env *env, t_pipex *pipex)
{
	ft_putendl_fd("exit", 2);
	free_split(env->cmds, ft_strstrlen(env->cmds));
	free_split(env->clean_cmds, ft_strstrlen(env->clean_cmds));
	free_split(env->envp, ft_strstrlen(env->envp));
	parent_free(pipex);
	exit(0);
}

void	ft_exit_error(t_env *env, int status)
{
	ft_putendl_fd("exit", 2);
	free_split(env->envp, ft_strstrlen(env->envp));
	exit(status);
}
