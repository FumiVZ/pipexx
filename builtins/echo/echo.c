/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 17:55:35 by machrist          #+#    #+#             */
/*   Updated: 2024/05/27 18:23:01 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_echo(t_env *env, char **args)
{
	size_t	i;
	size_t	j;
	bool	n;

	i = 1;
	n = false;
	if (!args[1])
	{
		ft_putchar_fd('\n', 1);
		env->status = 0;
		return ;
	}
	while (!ft_strncmp(args[i], "-n", 2))
	{
		j = 2;
		while (args[i][j] == 'n')
			++j;
		if (args[i][j])
			break ;
		if (!args[i + 1])
			return ;
		++i;
		n = true;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putchar_fd(' ', 1);
		++i;
	}
	if (!n)
		ft_putchar_fd('\n', 1);
	env->status = 0;
}

