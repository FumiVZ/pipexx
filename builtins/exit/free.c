/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:47:09 by machrist          #+#    #+#             */
/*   Updated: 2024/02/22 17:45:01 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_free(t_history *history, char *line)
{
	t_history	*tmp;

	while (history)
	{
		tmp = history;
		history = history->next;
		if (tmp->line) 
			free(tmp->line);
		free_split(tmp->cmd_all, ft_strstrlen(tmp->cmd_all));
		if (tmp)
			free(tmp);
	}
	if (line)
		free(line);
}
