/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:46:38 by machrist          #+#    #+#             */
/*   Updated: 2024/02/22 16:47:05 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_exit(t_history *history)
{
	ft_putendl_fd("exit", 1);
	ft_free(history, NULL);
	exit(0);
}

void	ft_exit_error(t_history *history, char *line)
{
	ft_free(history, line);
	exit(1);
}
