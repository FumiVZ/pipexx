/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:45:49 by machrist          #+#    #+#             */
/*   Updated: 2024/03/13 16:05:51 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_export_env(t_env *env, char *var)
{
	t_envp	*tmp;
	size_t	i;

	tmp = env->envp;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, var, ft_strlen(var) + 1))
		{
			free(tmp->value);
			tmp->value = ft_strdup(var + ft_strlen(tmp->name) + 1);
			return ;
		}
		tmp = tmp->next;
	}
	i = 0;
	while (var[i] && var[i] != '=')
		++i;
	var[i] = '\0';
	ft_add_envp(env, var, var + i + 1);
}

void	ft_export(t_env *env, char **cmd)
{
	size_t	i;

	i = 1;
	while (cmd[i])
	{
		ft_export_env(env, cmd[i]);
		++i;
	}
}
