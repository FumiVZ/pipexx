/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:19:20 by machrist          #+#    #+#             */
/*   Updated: 2024/02/22 18:45:43 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_setenv(char *name, char *value, t_env *env)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strjoin(name, "=");
	tmp2 = ft_strjoin(tmp, value);
	free(tmp);
	ft_export(tmp2, env);
	free(tmp2);
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
