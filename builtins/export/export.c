/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:45:49 by machrist          #+#    #+#             */
/*   Updated: 2024/03/13 16:23:22 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_export_env(t_env *env, char *var)
{
	t_envp	*tmp;
	char	*value;
	size_t	i;

	i = 0;
	while (var[i] && var[i] != '=')
		++i;
	if (!var[i])
		value = NULL;
	else
		value = var + i + 1;
	var[i] = '\0';
	tmp = env->envp;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, var, ft_strlen(var) + 1))
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return ;
		}
		tmp = tmp->next;
	}
	ft_add_envp(env, var, value);
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
