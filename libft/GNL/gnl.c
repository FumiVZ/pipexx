/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:58:09 by machrist          #+#    #+#             */
/*   Updated: 2024/02/21 17:59:50 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

static int	polish_list(t_list **list)
{
	t_list		*last_node;
	t_list		*clean_node;
	size_t		i;
	size_t		j;
	char		*buf;

	buf = malloc(BUFFER_SIZE + 1);
	clean_node = malloc(sizeof(t_list));
	if (!buf || !clean_node)
	{
		dealloc_list(list, clean_node, buf);
		return (0);
	}
	last_node = find_last(*list);
	i = 0;
	j = 0;
	while (last_node && last_node->content[i] && last_node->content[i] != '\n')
		++i;
	while (last_node && last_node->content[i] && last_node->content[++i])
		buf[j++] = last_node->content[i];
	buf[j] = '\0';
	clean_node->content = buf;
	clean_node->next = NULL;
	dealloc_list(list, clean_node, buf);
	return (1);
}

static char	*ft_get_line(t_list *list)
{
	size_t		str_len;
	char		*line;

	if (!list)
		return (NULL);
	str_len = len_to_newline(list);
	line = malloc(str_len + 1);
	if (!line)
		return (NULL);
	copy_str(list, line);
	if (!line)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

static int	append(t_list **list, char *buf)
{
	t_list	*new;
	t_list	*last;

	last = find_last(*list);
	new = malloc(sizeof(t_list));
	if (!new)
	{
		free(buf);
		return (0);
	}
	if (!last)
		*list = new;
	else
		last->next = new;
	new->content = buf;
	new->next = NULL;
	return (1);
}

static void	ft_create_list(t_list **list, int fd)
{
	long long		char_read;	
	char			*buf;

	while (!found_newline(*list))
	{
		buf = malloc(BUFFER_SIZE + 1);
		if (!buf)
			return (dealloc_list(list, NULL, NULL));
		char_read = read(fd, buf, BUFFER_SIZE);
		if (char_read == -1 || char_read == 0)
		{
			if (char_read == -1)
				dealloc_list(list, NULL, NULL);
			return (free(buf));
		}
		buf[char_read] = '\0';
		if (!append(list, buf))
			return (dealloc_list(list, NULL, NULL));
	}
}

char	*get_next_line(int fd)
{
	static t_list	*list = NULL;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		dealloc_list(&list, NULL, NULL);
		return (NULL);
	}
	ft_create_list(&list, fd);
	if (!list)
		return (NULL);
	line = ft_get_line(list);
	if (!line)
	{
		dealloc_list(&list, NULL, NULL);
		return (NULL);
	}
	if (!polish_list(&list) && line)
	{
		free(line);
		return (NULL);
	}
	return (line);
}
