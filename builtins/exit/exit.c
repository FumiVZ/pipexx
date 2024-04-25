/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:46:38 by machrist          #+#    #+#             */
/*   Updated: 2024/04/25 14:38:39 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_exit(t_env *env)
{
	ft_putendl_fd("exit", 2);
	free_split(env->cmds, ft_strstrlen(env->cmds));
	free_split(env->clean_cmds, ft_strstrlen(env->clean_cmds));
	free_split(env->envp, ft_strstrlen(env->envp));
	exit(0);
}

void	ft_exit_error(t_env *env, int status)
{
	ft_putendl_fd("exit", 2);
	free_split(env->envp, ft_strstrlen(env->envp));
	exit(status);
}
