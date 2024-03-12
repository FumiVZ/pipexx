/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnlu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:59:11 by machrist          #+#    #+#             */
/*   Updated: 2024/02/21 17:59:29 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"

void	copy_str(t_list *list, char *str)
{
	size_t	i;
	size_t	j;

	if (!list)
		return ;
	j = 0;
	while (list)
	{
		i = 0;
		while (list->content[i])
		{
			if (list->content[i] == '\n')
			{
				str[j++] = '\n';
				str[j] = '\0';
				return ;
			}
			str[j++] = list->content[i++];
		}
		list = list->next;
	}
	str[j] = '\0';
}

size_t	len_to_newline(t_list *list)
{
	size_t	i;
	size_t	len;

	if (!list)
		return (0);
	len = 0;
	while (list)
	{
		i = 0;
		while (list->content[i])
		{
			if (list->content[i++] == '\n')
				return (++len);
			++len;
		}
		list = list->next;
	}
	return (len);
}

int	found_newline(t_list *list)
{
	size_t	i;

	if (!list)
		return (0);
	while (list)
	{
		i = 0;
		while (list->content[i])
			if (list->content[i++] == '\n')
				return (1);
		list = list->next;
	}
	return (0);
}

t_list	*find_last(t_list *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

void	dealloc_list(t_list **list, t_list *clean_node, char *buf)
{
	t_list	*tmp;

	if (!*list)
		return ;
	while (*list)
	{
		tmp = (*list)->next;
		free((*list)->content);
		free(*list);
		*list = tmp;
	}
	*list = NULL;
	if (!clean_node && buf)
		free(buf);
	else if (clean_node && !buf)
		free(clean_node);
	else if (!clean_node && !buf)
		return ;
	else if (clean_node->content[0])
		*list = clean_node;
	else
	{
		free(buf);
		free(clean_node);
	}
}
