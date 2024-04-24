/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parthing.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:44:21 by machrist          #+#    #+#             */
/*   Updated: 2024/04/24 22:30:15 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARTHING_H
# define PARTHING_H

# include <dirent.h>
# include <libft.h>
# include <stdbool.h>
# include <stdio.h>
# include <sys/stat.h>

# define MALLOC "malloc failed"
# define GETCWD "getcwd failed"
# define STAT "stat failed"

char	*wildcard_match(const char *pattern);
char	**ft_word_spliting(char const *s);
void	pattern_matching(char **str, char **env);
bool	is_space(char c);
bool	is_special(char c);
bool	is_special_cpt(char const *c, size_t *i);
char	*crt_is_special(char const *s, size_t *j);
size_t	get_len_name(char *str);
char	*get_value(char *str, char **env);
char	*new_str(char *str, char *value, size_t len);
char	*sort_result(char *result);
int		msg_err(char *err);
void	*msg_err_ptr(char *err);

#endif