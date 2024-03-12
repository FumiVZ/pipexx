/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:58:30 by machrist          #+#    #+#             */
/*   Updated: 2024/02/21 17:58:56 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_H
# define GNL_H

# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}				t_list;

char	*get_next_line(int fd);
int		found_newline(t_list *list);
void	dealloc_list(t_list **list, t_list *clean_node, char *buf);
size_t	len_to_newline(t_list *list);
void	copy_str(t_list *list, char *str);
t_list	*find_last(t_list *list);

#endif