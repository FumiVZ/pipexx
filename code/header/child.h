/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 17:28:47 by machrist          #+#    #+#             */
/*   Updated: 2024/05/23 13:37:57 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHILD_H
# define CHILD_H

# include "pipex.h"
# include <minishell.h>
# include "struct.h"
# include "error.h"
# include <libft.h>
# include <fcntl.h>

void	child_free(t_pipex *pipex, char **env);
void	open_redir(t_env *env);
int		msg(char *err);
void	msg_error_cmd(char *err, t_cmd cmds);
void	msg_error(char *err, t_pipex *pipex);
void	parent_free(t_pipex *pipex);
void	close_pipes(t_pipex *pipex, t_cmd *cmd);
void	parse_cmd(t_pipex *pipex, t_cmd *cmds);
void	ft_exit(t_env *env, t_pipex *pipex, char **str);
int		here_doc(t_pipex *pipex, char *infile_name);
char	*collect_heredoc_input(char *delimiter);

#endif