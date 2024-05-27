/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:46:38 by machrist          #+#    #+#             */
/*   Updated: 2024/05/27 14:28:40 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// static bool	check_digit(char *str)
// {
// 	size_t	i;

// 	i = 0;
// 	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\r' || str[i] == '\f')
// 		i++;
// 	if (str[i] == '-' || str[i] == '+')
// 		i++;
// 	while (str[i])
// 	{
// 		if (!ft_isdigit(str[i]))
// 			return (false);
// 		i++;
// 		while (str[i] == ' ' || str[i] == '\t' || str[i] == '\r'
// 			|| str[i] == '\f')
// 		{
// 			i++;
// 			if ((str[i] != ' ' || str[i] != '\t' || str[i] != '\r'
// 			|| str[i] != '\f') && !str[i])
// 				return (true);
// 		}
// 	}
// 	return (true);
// }

void	basic_exit(t_env *env, t_pipex *pipex, char **str)
{
	if (!str[1])
	{
		parent_free(pipex);
		free_split(env->envp, ft_strstrlen(env->envp));
		exit(0);
	}
	if (str[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		parent_free(pipex);
		free_split(env->envp, ft_strstrlen(env->envp));
		exit(1);
	}
}

void	ft_exit(t_env *env, t_pipex *pipex, char **str)
{
	int	status;

	if (!ft_is_int(str[1]))
	{
		ft_printf_fd(2, "minishell: exit: %s: numeric argument required\n",
			str[1]);
		parent_free(pipex);
		free_split(env->envp, ft_strstrlen(env->envp));
		exit(2);
	}
	basic_exit(env, pipex, str);
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
