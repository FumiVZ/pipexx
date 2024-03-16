/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:46:38 by machrist          #+#    #+#             */
/*   Updated: 2024/03/16 22:39:54 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_exit(t_env *env, char **cmd)
{
	ft_putendl_fd("exit", 1);
	free_split(cmd, ft_strstrlen(cmd));
	free_split(env->clean_cmds, ft_strstrlen(env->clean_cmds));
	int i = 0;
	while (env->envp[i])
	{
		printf("%s\n", env->envp[i]);
		i++;
	}
	free_split(env->envp, ft_strstrlen(env->envp));
	exit(0);
}

void	ft_exit_error(t_env *env, int status)
{
	free_split(env->envp, ft_strstrlen(env->envp));
	exit(status);
}
