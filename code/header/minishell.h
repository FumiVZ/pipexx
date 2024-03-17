/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:18:44 by machrist          #+#    #+#             */
/*   Updated: 2024/03/17 18:07:31 by machrist         ###   ########.fr       */
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
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>

# define ERR_FILE "minishell: %s: %s\n"
# define ERR_INPUT "Invalid number of arguments."
# define ERR_PIPE "pipe failed"
# define ERR_CMD "minishell: %s: command not found\n"
# define ERR_CMD_EMPTY "pipex: command not found\n"
# define ERR_FORK "fork failed"
# define ERR_MALLOC "malloc failed"
# define ERR_ACCESS "minishell: %s: permission denied\n"
# define ERR_ACCESS_EMPTY "minishell: permission denied\n"

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
	char				**envp;
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

void					ft_exit(t_env *env, char **cmd);
void					ft_exit_error(t_env *env, int status);
void					ft_env(t_env *env);
void					ft_echo(char **args);
void					ft_pwd(void);
void					ft_cd(char **args, t_env *env);
void					ft_export(t_env *env, char **cmd);
void					ft_unset(t_env *env, char **cmd);
int						is_sep(char *s);
int						exec_cmd(t_env *env, t_redir *redir);
size_t					len_cmd(char **cmd);
char					**sep_case(char **cmds);
char					**create_cmd(char **cmds);
void					pattern_matching(char **str, char **env);
char					**ft_word_spliting(char const *s);
void					quote_removal(char **str);
void					ft_free_child(t_env *env);
void					ft_free_parent(t_env *env);
char					**ft_init_env(char **envp);
char					**ft_export_env(t_env *env, char *var);
void					open_redir(t_env *env);
char					*ft_color(void);

#endif