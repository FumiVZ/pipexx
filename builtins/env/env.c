/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 17:53:18 by machrist          #+#    #+#             */
/*   Updated: 2024/05/27 16:14:43 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_env(t_env *env)
{
	size_t	i;

	i = 0;
	while (env->envp[i])
	{
		printf("%s\n", env->envp[i]);
		i++;
	}
	env->status = 0;
}

void	ft_env_export(t_env *env)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (env->envp[i])
	{
		printf("declare -x ");
		j = 0;
		while(env->envp[i][j] && env->envp[i][j] != '=')
			printf("%c", env->envp[i][j++]);
		if (env->envp[i][j] == '=')
			printf("=\"%s\"\n", env->envp[i] + j + 1);
		else
			printf("\n");
		i++;
	}
	env->status = 0;
}