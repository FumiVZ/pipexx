/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincent <vincent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:13:52 by vincent           #+#    #+#             */
/*   Updated: 2024/03/14 14:57:50 by vincent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_redir(t_redir redir)
{
	redir.cmd = NULL;
	redir.prev_pid = 0;
	redir.sep = 0;
	redir.next_sep = 0;
	redir.fd_in = 0;
	redir.fd_out = 1;
	redir.paths = NULL;
}

void	redirection(t_env *env)
{
	(void) env;
}
