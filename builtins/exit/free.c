/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:47:09 by machrist          #+#    #+#             */
/*   Updated: 2024/03/16 14:59:31 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_free(t_env *env)
{
	t_envp	*tmp_envp;
	t_set	*tmp_set;

	while (env->envp)
	{
		tmp_envp = env->envp;
		env->envp = env->envp->next;
		if (tmp_envp->name)
			free(tmp_envp->name);
		if (tmp_envp->value)
			free(tmp_envp->value);
		if (tmp_envp)
			free(tmp_envp);
	}
	while (env->set)
	{
		tmp_set = env->set;
		env->set = env->set->next;
		if (tmp_set->name)
			free(tmp_set->name);
		if (tmp_set->value)
			free(tmp_set->value);
		if (tmp_set)
			free(tmp_set);
	}
}
