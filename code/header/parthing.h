/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parthing.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:44:21 by machrist          #+#    #+#             */
/*   Updated: 2024/04/25 17:44:51 by machrist         ###   ########.fr       */
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
# define ERR_OPEN "open failed"
# define ERR_READ "read failed"
# define ERR_CLOSE "close failed"
# define ERR_DUP2 "dup2 failed"
# define ERR_PIPE "pipe failed"
# define ERR_FORK "fork failed"
# define ERR_EXECVE "execve failed"
# define ERR_WAITPID "waitpid failed"
# define ERR_ACCESS "permission denied"
# define ERR_CMD "command not found"
# define ERR_CMD_EMPTY "command not found"
# define ERR_PAR "minishell: syntax error near unexpected token `('"
# define ERR_UNDEFINE "syntax error near $() undefine behavior"
# define ERR_TOKEN "minishell: syntax error near unexpected token"

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