/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 17:20:40 by machrist          #+#    #+#             */
/*   Updated: 2024/06/12 18:00:33 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <sys/wait.h>
# include <stdbool.h>

typedef struct s_cmd
{
	char			**args;
	int				*infiles;
	char			**infiles_name;
	int				*outfiles;
	char			**outfiles_name;
	int				id;
	int				*pipe;
	int				exec;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_pipex
{
	pid_t			*pid;
	int				i;
	char			**paths;
	char			*cmd_paths;
	char			**cmd;
	int				cmd_nmbs;
	int				nb_pipes;
	int				old0;
	int				old1;
	struct s_env	*env;
	struct s_cmd	*cmds;
	bool			is_dir;
}	t_pipex;

typedef struct s_env
{
	char	**envp;
	char	**cmds;
	char	**clean_cmds;
	int		status;
}			t_env;

void	print_tab(char **tab);
int		count_pipes(t_pipex *pipex);
void	close_pipes(t_pipex *pipex, t_cmd *cmd);
void	close_files(t_pipex	*pipex, t_cmd *cmd);
void	pipe_handle(t_pipex *pipex, t_cmd *cmd);
void	crt_pipes(t_pipex *pipex, t_cmd *cmd);
void	parent_free(t_pipex *pipex);
void	msg_error_outfile(char *err, t_pipex pipex, char *outfiles_name);
void	msg_error_infile(char *err, t_pipex pipex, char *infile_name);

#endif