/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:46:38 by machrist          #+#    #+#             */
/*   Updated: 2024/03/13 15:33:11 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_exit(t_env *env, char **cmd)
{
	ft_putendl_fd("exit", 1);
	free_split(cmd, ft_strstrlen(cmd));
	ft_free(env);
	exit(0);
}

void	ft_exit_error(t_env *env)
{
	ft_free(env);
	exit(1);
}
