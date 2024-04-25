/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 17:55:35 by machrist          #+#    #+#             */
/*   Updated: 2024/04/25 14:47:18 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_echo(t_env *env, char **args)
{
	size_t	i;

	i = 1;
	if (!args[1])
	{
		ft_putchar_fd('\n', 1);
		env->status = 0;
		return ;
	}
	if (!ft_strncmp(args[1], "-n", 3))
		++i;
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putchar_fd(' ', 1);
		++i;
	}
	if (ft_strncmp(args[1], "-n", 3))
		ft_putchar_fd('\n', 1);
	env->status = 0;
}
