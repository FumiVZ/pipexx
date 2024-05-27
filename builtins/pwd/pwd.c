/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:15:47 by machrist          #+#    #+#             */
/*   Updated: 2024/05/28 00:02:40 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_pwd(t_env *env)
{
	char	*pwd;

	pwd = ft_getenv(env->envp, "PWD");
	if (!pwd)
	{
		env->status = 1;
		printf("\n");
		init_pwd(env);
		return ;
	}
	printf("%s\n", pwd);
	init_pwd(env);
	env->status = 0;
}
