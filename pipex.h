/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 10:53:51 by vzuccare          #+#    #+#             */
/*   Updated: 2024/02/02 15:53:14 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./libft/libft.h"
# include "./libft/ft_printf.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_pipex
{
	int		pid1;
	int		pid2;
	int		fd[2];
	int		infile;
	int		outfile;
	char	*path;
	char	**cmd_path;
	char	**args;
	char	*cmd;
}	t_pipex;

int		parse_env(char **env, char **av, t_pipex *list);
char	*can_acess(char *cmd, char **cmd_path);

#endif