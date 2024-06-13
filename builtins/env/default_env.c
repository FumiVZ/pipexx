/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 22:30:50 by machrist          #+#    #+#             */
/*   Updated: 2024/06/13 16:32:17 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_envp(char **envp)
{
	ft_printf_fd(2, "minishell: error malloc\n");
	free_split(envp, ft_strstrlen(envp));
	envp = NULL;
}

void	init_pwd(t_env *env)
{
	char	*pwd;
	char	*tmp;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (free_envp(env->envp));
	tmp = malloc(ft_strlen("PWD=") + ft_strlen(pwd) + 1);
	if (!tmp)
	{
		free(pwd);
		return (free_envp(env->envp));
	}
	ft_strlcpy(tmp, "PWD=", ft_strlen("PWD=") + 1);
	ft_strlcat(tmp, pwd, ft_strlen("PWD=") + ft_strlen(pwd) + 1);
	free(pwd);
	add_value_to_env(env, tmp);
}

void	init_shlvl(t_env *env)
{
	char	*shlvl;
	char	*tmp;
	long	lvl;

	shlvl = ft_getenv(env->envp, "SHLVL");
	if (!shlvl || !ft_is_int(shlvl) || !ft_check_num(shlvl))
	{
		tmp = ft_strdup("SHLVL=1");
		if (!tmp)
			return (free_envp(env->envp));
		add_value_to_env(env, tmp);
		return ;
	}
	lvl = check_shlvl(shlvl);
	tmp = ft_itoa(lvl);
	if (!tmp)
		return (free_envp(env->envp));
	shlvl = ft_strjoin("SHLVL=", tmp);
	free(tmp);
	if (!shlvl)
		return (free_envp(env->envp));
	add_value_to_env(env, shlvl);
}

void	init_last_param(t_env *env, int ac, char **av)
{
	char	*last_param;
	char	*tmp;

	last_param = ft_getenv(env->envp, "_");
	if (!last_param)
	{
		if (av[ac - 1] && ft_strncmp(av[ac - 1], "$_", 2))
			tmp = ft_strjoin("_=", "/usr/bin/bash");
		else
			tmp = ft_strjoin("_=", av[ac - 1]);
		if (!tmp)
			return (free_envp(env->envp));
		add_value_to_env(env, tmp);
		return ;
	}
	tmp = ft_strjoin("_=", last_param);
	if (!tmp)
		return (free_envp(env->envp));
	add_value_to_env(env, tmp);
}

void	set_last_param(t_env *env, char *last_param)
{
	char	*tmp;

	// if (!last_param)
	// {
	// 	tmp = ft_strdup("_=");
	// 	if (!tmp)
	// 		return (free_envp(env->envp));
	// 	add_value_to_env(env, tmp);
	// 	return ;
	// }
	tmp = ft_strjoin("_=", last_param);
	if (!tmp)
		return (free_envp(env->envp));
	add_value_to_env(env, tmp);
}
