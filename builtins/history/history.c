/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:59:59 by machrist          #+#    #+#             */
/*   Updated: 2024/02/22 17:52:16 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_history	*find_last_history(t_env *env)
{
	t_history	*tmp;

	if (!env->history)
		return (NULL);
	tmp = env->history;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	ft_init_history(t_env *env, char *line)
{
	t_history			*new;
	t_history			*last;

	if (!line)
		ft_exit_error(env->history, line);
	last = find_last_history(env);
	new = malloc(sizeof(t_history));
	if (!new)
		ft_exit_error(env->history, line);
	new->line = line;
	new->cmd_all = ft_split_command(line);
	new->next = NULL;
	if (!new->cmd_all)
		ft_exit_error(env->history, line);
	if (!last)
	{
		new->id = 1;
		env->history = new;
		return ;
	}
	new->id = last->id + 1;
	last->next = new;
}

void	ft_history(t_history *history)
{
	while (history)
	{
		ft_printf_fd(1, "	%d  %s\n", history->id, history->line);
		history = history->next;
	}
}
