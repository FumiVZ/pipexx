/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 17:53:18 by machrist          #+#    #+#             */
/*   Updated: 2024/03/16 14:59:26 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_env(t_env *env)
{
	t_envp	*tmp_envp;

	tmp_envp = env->envp;
	while (tmp_envp)
	{
		printf("%s=%s\n", tmp_envp->name, tmp_envp->value);
		tmp_envp = tmp_envp->next;
	}
}
