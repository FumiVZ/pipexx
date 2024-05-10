/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincent <vincent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:46:38 by machrist          #+#    #+#             */
/*   Updated: 2024/05/04 17:37:50 by vincent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <pipex.h>
#include <struct.h>
#include <error.h>

void	ft_exit(t_env *env, t_pipex *pipex)
{
	parent_free(pipex);
	free_split(env->envp, ft_strstrlen(env->envp)); 
	exit(0);
}

void	ft_exit_error(t_env *env, int status)
{
	ft_putendl_fd("exit", 2);
	if (env->envp)
		free_split(env->envp, ft_strstrlen(env->envp));
	exit(status);
}
