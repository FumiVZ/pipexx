/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:19:20 by machrist          #+#    #+#             */
/*   Updated: 2024/03/13 15:12:57 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_setenv(char *name, char *value, t_env *env)
{
	t_envp	*tmp;

	tmp = env->envp;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, name, ft_strlen(name) + 1))
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return ;
		}
		tmp = tmp->next;
	}
	ft_add_envp(env, name, value);
}

void	ft_cd(char **args, t_env *env)
{
	char	*oldpwd;
	char	*pwd;

	oldpwd = getcwd(NULL, 0);
	if (chdir(args[1]) == -1)
	{
		printf("minishell: cd: %s: %s\n", args[1], strerror(errno));
		return ;
	}
	pwd = getcwd(NULL, 0);
	ft_setenv("OLDPWD", oldpwd, env);
	ft_setenv("PWD", pwd, env);
	free(oldpwd);
	free(pwd);
}
