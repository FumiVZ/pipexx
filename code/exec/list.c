/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincent <vincent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 17:20:05 by vzuccare          #+#    #+#             */
/*   Updated: 2024/05/31 14:32:12 by vincent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

void	free_files(t_cmd *head)
{
	int		i;

	i = 0;
	if (head->infiles_name)
	{
		while (head->infiles_name[i])
		{
			free(head->infiles_name[i]);
			i++;
		}
		free(head->infiles_name);
		free(head->infiles);
	}
	i = 0;
	if (head->outfiles_name)
	{
		while (head->outfiles_name[i])
		{
			free(head->outfiles_name[i]);
			i++;
		}
		free(head->outfiles_name);
		free(head->outfiles);
	}
}

void	free_l(t_cmd *head)
{
	t_cmd	*tmp;
	int		i;

	while (head)
	{
		i = -1;
		if (head->args)
		{
			while (head->args[++i])
				free(head->args[i]);
			free(head->args);
		}
		free_files(head);
		if (head->pipe)
			free(head->pipe);
		tmp = head;
		head = head->next;
		free(tmp);
	}
	free(head);
}

void	list_init(t_cmd *head)
{
	head->args = NULL;
	head->infiles = NULL;
	head->infiles_name = NULL;
	head->outfiles = NULL;
	head->outfiles_name = NULL;
	head->next = NULL;
	head->pipe = NULL;
	head->pipeid = 0;
	head->exec = 1;
}

void	close_reset(int fd, int fd2)
{
	close(fd);
	close(fd2);
	fd = -1;
	fd2 = -1;
}
