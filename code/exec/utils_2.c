/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:43:32 by vincent           #+#    #+#             */
/*   Updated: 2024/06/11 17:56:12 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	secure_dup2(int oldfd, int newfd, t_pipex *pipex)
{
	if (dup2(oldfd, newfd) == -1)
		msg_error(ERR_DUP2, pipex);
}