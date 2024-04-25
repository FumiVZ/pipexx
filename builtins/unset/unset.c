/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:47:33 by machrist          #+#    #+#             */
/*   Updated: 2024/04/25 14:50:44 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	**new_envp(t_env *env, char *var)
{
	char	**new;
	size_t	i;
	size_t	j;

	new = malloc(sizeof(char *) * (ft_strstrlen(env->envp)));
	if (!new)
	{
		perror("minishell: error malloc");
		return (NULL);
	}
	i = 0;
	j = 0;
	while (env->envp[i])
	{
		if (ft_strncmp(env->envp[i], var, ft_strlen(var) + 1))
		{
			new[j] = ft_strdup(env->envp[i]);
			j++;
		}
		i++;
	}
	new[j] = NULL;
	free_split(env->envp, ft_strstrlen(env->envp));
	return (new);
}

static char	**ft_unset_envp(t_env *env, char *var)
{
	size_t	i;
	char	**new;

	i = 0;
	while (env->envp[i])
	{
		if (!ft_strncmp(env->envp[i], var, ft_strlen(var) + 1))
		{
			new = new_envp(env, var);
			if (new)
				return (new);
			else
			{
				env->status = 1;
				return (env->envp);
			}
		}
		i++;
	}
	return (env->envp);
}

void	ft_unset(t_env *env, char **cmd)
{
	size_t	i;
	char	**new;

	if (!cmd[1])
		return ;
	i = 1;
	while (cmd[i])
	{
		new = ft_unset_envp(env, cmd[i]);
		if (!new)
			return ;
		++i;
	}
}
