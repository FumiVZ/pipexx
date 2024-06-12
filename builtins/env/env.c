/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 17:53:18 by machrist          #+#    #+#             */
/*   Updated: 2024/06/12 17:34:34 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

long	check_shlvl(char *shlvl)
{
	long	lvl;

	lvl = ft_strtol(shlvl);
	if (lvl == -3147483649)
	{
		ft_putendl_fd("minishell: warning: shell level (1147483648) too high, \
resetting to 1", 2);
		lvl = 0;
	}
	if (lvl == 4294967296)
		lvl = 0;
	if (lvl >= INT_MAX || lvl < -1000)
		lvl = -1;
	else if (lvl > 999)
	{
		ft_printf_fd(2, "minishell: warning: shell level (%d) too high, \
resetting to 1\n", lvl + 1);
		lvl = 0;
	}
	lvl++;
	return (lvl);
}

void	ft_env(t_env *env)
{
	size_t	i;

	i = 0;
	while (env->envp[i])
	{
		printf("%s\n", env->envp[i]);
		i++;
	}
	env->status = 0;
}

void	ft_env_export(t_env *env)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (env->envp[i])
	{
		if (!ft_strncmp(env->envp[i], "_=", 2))
		{
			i++;
			continue ;
		}
		printf("declare -x ");
		j = 0;
		while(env->envp[i][j] && env->envp[i][j] != '=')
			printf("%c", env->envp[i][j++]);
		if (env->envp[i][j] == '=')
			printf("=\"%s\"\n", env->envp[i] + j + 1);
		else
			printf("\n");
		i++;
	}
	env->status = 0;
}
