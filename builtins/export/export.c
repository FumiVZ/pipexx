/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:45:49 by machrist          #+#    #+#             */
/*   Updated: 2024/05/25 17:50:07 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	error_env(t_env *env, char **new, size_t i)
{
	free_split(new, i);
	ft_putstr_fd("minishell: export: failed", 2);
	ft_exit_error(env, 1);
}

static char	**new_envp(t_env *env, char *var)
{
	char	**new;
	size_t	i;

	new = malloc(sizeof(char *) * (ft_strstrlen(env->envp) + 2));
	if (!new)
	{
		perror("minishell: error malloc");
		return (env->envp);
	}
	i = 0;
	while (env->envp[i])
	{
		new[i] = ft_strdup(env->envp[i]);
		if (!new[i])
			error_env(env, new, i);
		i++;
	}
	new[i] = ft_strdup(var);
	if (!new[i])
		error_env(env, new, i);
	new[i + 1] = NULL;
	free_split(env->envp, ft_strstrlen(env->envp));
	return (new);
}

char	**ft_export_env(t_env *env, char *var)
{
	size_t	i;
	size_t	len;

	len = 0;
	while (var[len] && var[len] != '=')
		len++;
	if (!var[len])
		return (env->envp);
	i = 0;
	while (env->envp[i])
	{
		if (!ft_strncmp(env->envp[i], var, len))
		{
			free(env->envp[i]);
			env->envp[i] = ft_strdup(var);
			return (env->envp);
		}
		i++;
	}
	return (new_envp(env, var));
}

static	bool	is_identifier(char *str)
{
	size_t	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (false);
	i++;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

void	ft_export(t_env *env, char **cmd)
{
	size_t	i;

	i = 1;
	while (cmd[i])
	{
		if (!is_identifier(cmd[i]))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(cmd[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			env->status = 1;
		}
		env->envp = ft_export_env(env, cmd[i]);
		++i;
	}
}
