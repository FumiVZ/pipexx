/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincent <vincent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:18:44 by machrist          #+#    #+#             */
/*   Updated: 2024/03/14 12:14:55 by vincent          ###   ########.fr       */
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

typedef struct s_set
{
	char				*name;
	char				*value;
	struct s_set		*next;
}						t_set;

typedef struct s_envp
{
	char				*name;
	char				*value;
	struct s_envp		*next;
}						t_envp;

typedef struct s_env
{
	t_set				*set;
	t_envp				*envp;
}						t_env;

/**
 * @brief Enumeration representing different types of separators.
 * END: No separator
 * HEREDOC: Here doc (<<) separator
 * APPEND: Append (>>) redirection separator
 * IN: Input (<) redirection separator
 * OUT: Output (>) redirection separator
 * PIPE: Pipe (|) separator
 * AND: AND (&&) separator
 * OR: OR (||) separator
 */

enum e_sep
{
	END,
	HERE_DOC,
	APPEND,
	IN,
	OUT,
	PIPE,
	AND,
	OR
};


int						has_bs(const char *s, size_t i);
int						ft_len_word(char const *s, char c, size_t i);
int						len_word(char const *s, char c, size_t i);
int						len_word_tot(char const *s, char c, size_t i);
char					**ft_split_command(char const *s);
void					ft_exit(t_env *env, char **cmd);
void					ft_exit_error(t_env *env);
void					ft_free(t_env *env);
int						command_end(char c);
char					**ft_split_line(char const *s);
int						has_bs(const char *s, size_t i);
void					ft_env(t_env *env);
void					ft_echo(char **args);
void					ft_pwd(void);
void					ft_cd(char **args, t_env *env);
void					ft_export(t_env *env, char **cmd);
void					ft_add_envp(t_env *env, char *name, char *value);
void					ft_unset(t_env *env, char **cmd);

#endif