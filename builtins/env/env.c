/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 17:53:18 by machrist          #+#    #+#             */
/*   Updated: 2024/03/16 20:04:49 by machrist         ###   ########.fr       */
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
}
