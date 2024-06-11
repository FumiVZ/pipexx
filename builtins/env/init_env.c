/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 18:06:32 by machrist          #+#    #+#             */
/*   Updated: 2024/06/02 19:00:12 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ft_getenv(char **envp, char *name)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(name);
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], name, len))
		{
			if (envp[i][len] != '=')
				return (NULL);
			return (envp[i] + len + 1);
		}
		i++;
	}
	return (NULL);
}

static void	alloc_env(char **new, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		new[i] = malloc(ft_strlen(envp[i]) + 1);
		if (!new[i])
		{
			free_split(new, i);
			perror("minishell: error malloc");
			exit(1);
		}
		ft_strlcpy(new[i], envp[i], ft_strlen(envp[i]) + 1);
		i++;
	}
	new[i] = NULL;
}

void	ft_init_env(t_env *env, char **envp)
{
	char	**new;

	new = malloc(sizeof(char *) * (ft_strstrlen(envp) + 1));
	if (!new)
	{
		perror("minishell: error malloc");
		exit(1);
	}
	alloc_env(new, envp);
	env->envp = new;
	set_default_env(env);
}

void	add_value_to_env(t_env *env, char *var)
{
	char	**new;
	size_t	i;
	size_t	j;
	bool	check;

	check = false;
	if (!var)
		return (free_envp(env->envp));
	new = malloc(sizeof(char *) * (ft_strstrlen(env->envp) + 2));
	if (!new)
		return (free_envp(env->envp));
	i = 0;
	j = 0;
	while (env->envp[i])
	{
		if (!ft_strncmp(env->envp[i], var, ft_strlen_c(var, '=')))
		{
			free(env->envp[i++]);
			new[j++] = var;
			check = true;
		}
		else
			new[j++] = env->envp[i++];
	}
	if (check == false)
		new[j++] = var;
	new[j] = NULL;
	free(env->envp);
	env->envp = new;
}

void	set_default_env(t_env *env)
{
	if (!env->envp)
		return ;
	init_pwd(env);
	init_shlvl(env);
}
