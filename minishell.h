/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:18:44 by machrist          #+#    #+#             */
/*   Updated: 2024/02/22 19:09:36 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>

typedef struct s_history
{
	char				**cmd_all;
	char				*line;
	unsigned long long	id;
	struct s_history	*next;
}						t_history;

typedef struct s_env
{
	t_history			*history;
	char				**envp;
}						t_env;

int						has_bs(const char *s, size_t i);
int						ft_len_word(char const *s, char c, size_t i);
int						len_word(char const *s, char c, size_t i);
int						len_word_tot(char const *s, char c, size_t i);
char					**ft_split_command(char const *s);
void					ft_exit(t_history *history);
void					ft_exit_error(t_history *history, char *line);
void					ft_init_history(t_env *env, char *line);
void					ft_history(t_history *history);
void					ft_free(t_history *history, char *line);
int						command_end(char c);
char					**ft_split_line(char const *s);
int						has_bs(const char *s, size_t i);
t_history				*find_last_history(t_env *env);
void					ft_env(t_env *env);
void					ft_echo(char **args);
void					ft_pwd(void);
void					ft_cd(char **args, t_env *env);
void					ft_export(char *str, t_env *env);

#endif