/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:47:33 by machrist          #+#    #+#             */
/*   Updated: 2024/02/22 18:48:49 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_unset_env(t_env *env, char *var)
{
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	while (env->envp[i])
	{
		len = ft_strlen(var);
		j = 0;
		while (env->envp[i][j] && env->envp[i][j] == var[j])
			++j;
		if (env->envp[i][j] == '=' && j == len)
		{
			free(env->envp[i]);
			while (env->envp[i])
			{
				env->envp[i] = env->envp[i + 1];
				++i;
			}
			return ;
		}
		++i;
	}
}

void	ft_unset(t_env *env, char **cmd)
{
	size_t	i;

	if (!cmd[1])
		return ;
	i = 1;
	while (cmd[i])
	{
		ft_unset_env(env, cmd[i]);
		++i;
	}
}
