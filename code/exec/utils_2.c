/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincent <vincent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:43:32 by vincent           #+#    #+#             */
/*   Updated: 2024/05/31 16:58:14 by vincent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void    secure_dup2(int oldfd, int newfd, t_pipex *pipex)
{
    if (dup2(oldfd, newfd) == -1)
        msg_error(ERR_DUP2, pipex);
}