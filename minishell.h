/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:18:44 by machrist          #+#    #+#             */
/*   Updated: 2024/03/16 16:43:02 by vzuccare         ###   ########lyon.fr   */
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

# define ERR_FILE "minishell: %s: %s\n"
# define ERR_INPUT "Invalid number of arguments."
# define ERR_PIPE "pipe failed"
# define ERR_CMD "minishell: %s: command not found\n"
# define ERR_CMD_EMPTY "pipex: command not found\n"
# define ERR_FORK "fork failed"
# define ERR_MALLOC "malloc failed"
# define ERR_ACCESS "minishell: %s: permission denied\n"
# define ERR_ACCESS_EMPTY "minishell: permission denied\n"

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

typedef struct s_redir
{
	char				*cmd;
	char				**args;
	char				*cmd_paths;
	int					pipefd[2];
	int					prev_pid;
	int					sep;
	int					infile;
	int					outfile;
	pid_t				pid;
	char				**paths;
}						t_redir;

typedef struct s_env
{
	t_set				*set;
	t_envp				*envp;
	t_redir				*redir;
	char				**cmds;
	char				**clean_cmds;
	int					status;
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
int						is_sep(char *s);
void					init_redir(t_env *env);
int						exec_cmd(t_env *env);
char					**create_cmd(char **cmds);

#endif