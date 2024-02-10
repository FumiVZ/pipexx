/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 18:32:43 by vzuccare          #+#    #+#             */
/*   Updated: 2024/02/10 13:54:45 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	first_fork(t_pipex *list, size_t i)
{
	int		fd[2];
	int		pid;
	int		status;

	fd[0] = list->infile;
	if (pipe(fd) == -1)
	{
		write(2, "Error: pipe failed\n", 19);
		return ;
	}
	pid = fork();
	if (pid < 0)
	{
		write(2, "Error: fork failed\n", 19);
		return ;
	}
	if (pid == 0)
	{
		dup2(fd[0], 0);
		close(fd[0]);
		close(fd[1]);
		execve(list->cmd_path[0], list->cmd, NULL);
		dup2(1, list->outfile);
	}
	wait(&status);
	return (status);
}

int	mid_forks(t_pipex *list, int ac, size_t iterate)
{
	int	fd[2];
	int	pid;
	int	status;

	if (pipe(fd) == -1)
	{
		write(2, "Error: pipe failed\n", 19);
		return ;
	}
	fd[0] = list->outfile;
	pid = fork();
	if (pid < 0)
	{
		write(2, "Error: fork failed\n", 19);
		return ;
	}
	if (pid == 0)
	{
		dup2(fd[0], 0);
		close(fd[0]);
		close(fd[1]);
		execve(list->cmd_path[ac], list->cmd, NULL);
		open(fd[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(1, fd[1]);
		close(fd[1]);
	}
	wait(&status);
	return (status);
}

int	last_fork(t_pipex *list, int ac)
{
	int	fd[2];	
	int	pid;
	int	status;

	if (pipe(fd) == -1)
	{
		write(2, "Error: pipe failed\n", 19);
		return ;
	}
	fd[0] = list->outfile;
	pid = fork();
	if (pid < 0)
	{
		write(2, "Error: fork failed\n", 19);
		return ;
	}
	if (pid == 0)
	{
		dup2(fd[0], 0);
		close(fd[0]);
		close(fd[1]);
		execve(list->cmd_path[ac], list->cmd, NULL);
		dup2(1, list->outfile);
	}
	wait(&status);
	return (status);
}