/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parthing.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:44:21 by machrist          #+#    #+#             */
/*   Updated: 2024/03/16 14:55:27 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARTHING_H
# define PARTHING_H

# include <libft.h>
# include <stdbool.h>
# include <dirent.h>
# include <stdio.h>

char	*wildcard_match(const char *pattern);
char	**ft_word_spliting(char const *s);
void	pattern_matching(char **str);
bool	is_space(char c);
bool	is_special(char c);
bool	is_special_cpt(char const *c, size_t *i);
char	*crt_is_special(char const *s, size_t *j);

#endif