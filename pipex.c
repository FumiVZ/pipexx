/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 10:33:12 by vzuccare          #+#    #+#             */
/*   Updated: 2024/02/02 15:57:41 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
/* 
void	print_tab(char **tab)
{
	size_t	i;

	i = -1;
	while (tab[++i])
		printf("%s\n", tab[i]);
}


int	pipex(t_pipex *list, char **envp)
{
	int		fd[2];
	int		pid;

	if (pipe(fd) == -1)
		return (write(2, "Error: fork failed\n", 19), 1);
	pid = fork();
	if (pid < 0)
		return (write(2, "Error: fork failed\n", 19), 2);
	if (pid == 0)
	{
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		//execve();
	}
	return (0);
} */

int	main(int ac, char **av, char **env)
{
	t_pipex	**list;
	int		fd[2];
	int		pid;

	(void) ac;
	list = malloc(sizeof(t_pipex **));
	*list = malloc(sizeof(t_pipex));
	if (!(*list))
		return (1);
	if (!list)
		return (1);
/* 	if (ac != 5)
		return (1); */
	parse_env(env, av, *list);
	(*list)->cmd = can_acess(av[1], (*list)->cmd_path);
	if (pipe(fd) == -1)
		return (write(2, "Error: fork failed\n", 19), 1);
	pid = fork();
	if (pid < 0)
		return (write(2, "Error: fork failed\n", 19), 2);
	if (pid == 0)
	{
/* 		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]); */
		execve((*list)->cmd, av, env);
		exit(0);
	}
	else
		waitpid(pid, NULL, 0);
	return (0);
}