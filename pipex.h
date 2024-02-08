/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 10:53:51 by vzuccare          #+#    #+#             */
/*   Updated: 2024/02/08 14:24:14 by vzuccare         ###   ########lyon.fr   */
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
# include <fcntl.h>

typedef struct s_pipex
{
	int		fd[2];
	int		infile;
	int		outfile;
	char	*path;
	char	**cmd_path;
	char	**args;
	char	**cmd;
}	t_pipex;

void	print_tab(char **tab);
char	*get_env_path(char **env);
char	**get_cmd(char **av, int ac);
char	**get_cmd_path(char *path, char **cmd);

#endif