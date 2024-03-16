/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:45:49 by machrist          #+#    #+#             */
/*   Updated: 2024/03/16 21:00:51 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	**new_envp(t_env *env, char *var)
{
	char	**new;
	size_t	i;

	new = malloc(sizeof(char *) * (ft_strstrlen(env->envp) + 2));
	if (!new)
		exit(1);
	i = 0;
	while (env->envp[i])
	{
		new[i] = ft_strdup(env->envp[i]);
		i++;
	}
	new[i] = ft_strdup(var);
	new[i + 1] = NULL;
	free_split(env->envp, ft_strstrlen(env->envp));
	return (new);
}

char	**ft_export_env(t_env *env, char *var)
{
	size_t	i;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	if (!var[i])
		return (env->envp);
	i = 0;
	while (env->envp[i])
	{
		if (!ft_strncmp(env->envp[i], var, ft_strlen(var) + 1))
		{
			free(env->envp[i]);
			env->envp[i] = ft_strdup(var);
			return (env->envp);
		}
		i++;
	}
	return (new_envp(env, var));
}

void	ft_export(t_env *env, char **cmd)
{
	size_t	i;

	i = 1;
	while (cmd[i])
	{
		env->envp = ft_export_env(env, cmd[i]);
		++i;
	}
}
