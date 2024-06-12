/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:49:45 by machrist          #+#    #+#             */
/*   Updated: 2024/06/12 17:49:48 by machrist         ###   ########.fr       */
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

int	msg_err_syntax(char *err, char c)
{
	ft_putstr_fd(err, 2);
	ft_putchar_fd('`', 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd("'\n", 2);
	return (0);
}