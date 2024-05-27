/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:46:38 by machrist          #+#    #+#             */
/*   Updated: 2024/05/27 18:02:08 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static bool	ft_check_num(char *nptr)
{
	int	i;

	i = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
		i++;
	if (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] != '\0')
		return (false);
	return (true);
}

void	basic_exit(t_env *env, t_pipex *pipex, char **str)
{
	int	exit_status;

	exit_status = 500;
	if (!str[1])
		exit_status = 0;
	else if (ft_check_num(str[1]) == false || !ft_is_int(str[1]))
	{
		ft_printf_fd(2, "minishell: exit: %s: numeric argument required\n",
			str[1]);
		exit_status = 2;
	}
	else if (str[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		exit_status = 1;
	}
	if (exit_status != 500)
	{
		parent_free(pipex);
		free_split(env->envp, ft_strstrlen(env->envp));
		exit(exit_status);
	}
}

void	ft_exit(t_env *env, t_pipex *pipex, char **str)
{
	int	status;

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
