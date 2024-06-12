/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 17:20:05 by vzuccare          #+#    #+#             */
/*   Updated: 2024/06/12 20:08:40 by vzuccare         ###   ########lyon.fr   */
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
			head->infiles[i] = -1;
			i++;
		}
		free(head->infiles_name);
		free(head->infiles);
		head->infiles_name = NULL;
	}
	i = 0;
	if (head->outfiles_name)
	{
		while (head->outfiles_name[i])
		{
			free(head->outfiles_name[i]);
			head->outfiles[i] = -1;
			i++;
		}
		free(head->outfiles_name);
		free(head->outfiles);
		head->outfiles_name = NULL;
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
	head->id = 0;
	head->exec = 1;
}

void	close_reset(int fd, int fd2)
{
	close(fd);
	close(fd2);
	fd = -1;
	fd2 = -1;
}

void	print_list(t_cmd *head)
{
	int i;
	int count = 0;
	t_cmd *tmp;

	i = 0;
	tmp = head;
	while (tmp)
	{
		ft_printf_fd(2, "count = %d\n", count);
		i = -1;
		ft_printf_fd(2, "id: %d\n", tmp->id);
		ft_printf_fd(2, "args: ");
		while (tmp->args[++i])
			ft_printf_fd(2, "%s ", tmp->args[i]);
		ft_printf_fd(2, "\n");
		count++;
		tmp = tmp->next;
	}
}