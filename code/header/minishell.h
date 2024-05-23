/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:18:44 by machrist          #+#    #+#             */
/*   Updated: 2024/05/23 13:38:12 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <fcntl.h>
# include <libft.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>
# include <struct.h>
# include <pipex.h>
# include <error.h>
# include <child.h>


# define ERR_FILE "minishell: %s: %s\n"
# define ERR_INPUT "Invalid number of arguments."
# define ERR_PIPE "pipe failed"
# define ERR_CMD "minishell: %s: command not found\n"
# define ERR_CMD_EMPTY "pipex: command not found\n"
# define ERR_FORK "fork failed"
# define ERR_MALLOC "malloc failed"
# define ERR_ACCESS "minishell: %s: permission denied\n"
# define ERR_ACCESS_EMPTY "minishell: permission denied\n"

void		ft_exit_error(t_env *env, int status);
void		ft_env(t_env *env);
void		ft_echo(t_env *env, char **args);
void		ft_pwd(t_env *env);
void		ft_cd(t_env *env, char **args);
void		ft_export(t_env *env, char **cmd);
void		ft_unset(t_env *env, char **cmd);
char		**pattern_matching(char **str, char **env, t_env *envp);
char		**ft_word_spliting(char const *s, char *arg);
void		quote_removal(char **str);
void		ft_free_child(t_env *env);
void		ft_free_parent(t_env *env);
char		**ft_init_env(char **envp);
char		**ft_export_env(t_env *env, char *var);
bool		check_syntax(char *str);
void		ft_readline(t_env *env);
char		*ft_getenv(char **envp, char *name);
void		msg_perror(t_env *env, char *err);
void		init_pipex(t_env *env);
char		*wildcard_match(const char *pattern);
void		check_for_parentheses(t_pipex *pipex);


#endif