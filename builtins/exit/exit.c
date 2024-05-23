/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:46:38 by machrist          #+#    #+#             */
/*   Updated: 2024/05/23 13:35:55 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <pipex.h>
#include <struct.h>
#include <error.h>

static bool	check_digit(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != '-' && str[i] != '+')
			return (false);
		i++;
	}
	return (true);
}

void	ft_exit(t_env *env, t_pipex *pipex, char **str)
{
	int	status;

	if (!str[1])
	{
		parent_free(pipex);
		free_split(env->envp, ft_strstrlen(env->envp));
		exit(0);
	}
	if (str[2])
	{
		ft_putstr_fd("exit: too many arguments", 2);
		parent_free(pipex);
		free_split(env->envp, ft_strstrlen(env->envp));
		exit(1);
	}
	if (!check_digit(str[1]))
	{
		ft_putstr_fd(" numeric argument required", 2);
		parent_free(pipex);
		free_split(env->envp, ft_strstrlen(env->envp));
		exit(2);
	}
	status = ft_atoi(str[1]);
	while (status > 255)
		status -= 256;
	while (status < 0)
		status += 256;
	parent_free(pipex);
	free_split(env->envp, ft_strstrlen(env->envp));
	exit(status);
	
}

void	ft_exit_error(t_env *env, int status)
{
	ft_putendl_fd("exit", 1);
	if (env->envp)
		free_split(env->envp, ft_strstrlen(env->envp));
	exit(status);
}
