/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:19:20 by machrist          #+#    #+#             */
/*   Updated: 2024/03/16 21:00:58 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
	ft_export_env(env, ft_strjoin("OLDPWD=", oldpwd));
	ft_export_env(env, ft_strjoin("PWD=", pwd));
	free(oldpwd);
	free(pwd);
}
