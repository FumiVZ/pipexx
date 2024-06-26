/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincent <vincent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:47:09 by machrist          #+#    #+#             */
/*   Updated: 2024/05/01 18:58:14 by vincent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_free_child(t_env *env)
{
	free_split(env->envp, ft_strstrlen(env->envp));
	free_split(env->cmds, ft_strstrlen(env->cmds));
	free_split(env->clean_cmds, ft_strstrlen(env->clean_cmds));
}

void	ft_free_parent(t_env *env)
{
	free_split(env->envp, ft_strstrlen(env->envp));
}
