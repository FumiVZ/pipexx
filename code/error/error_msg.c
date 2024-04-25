/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:49:45 by machrist          #+#    #+#             */
/*   Updated: 2024/04/25 17:45:04 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	msg_err(char *err)
{
	ft_printf_fd(2, err);
	return (0);
}

void	*msg_err_ptr(char *err)
{
	ft_printf_fd(2, err);
	return (NULL);
}

void	msg_perror(t_env *env, char *err)
{
	perror(err);
	env->status = 1;
}
