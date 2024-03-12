/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:45:49 by machrist          #+#    #+#             */
/*   Updated: 2024/02/22 18:57:35 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

size_t	ft_strlen_env(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != '=')
		++i;
	if (s[i] == '=')
		++i;
	return (i);
}

void	ft_export(char *str, t_env *env)
{
	char	**new_envp;
	size_t	i;

	i = 0;
	while (env->envp[i])
		++i;
	new_envp = malloc(sizeof(char *) * (i + 2));
	if (!new_envp)
		return ;
	i = 0;
	while (env->envp[i])
	{
		if (!ft_strncmp(env->envp[i], str, ft_strlen_env(str)))
		{
			free(env->envp[i]);
			env->envp[i] = str;
		}
		new_envp[i] = env->envp[i];
		++i;
	}
	new_envp[i] = str;
	new_envp[i + 1] = NULL;
	free(env->envp);
	env->envp = new_envp;
}
