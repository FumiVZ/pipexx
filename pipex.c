/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 10:33:12 by vzuccare          #+#    #+#             */
/*   Updated: 2024/02/10 13:39:15 by vzuccare         ###   ########lyon.fr   */
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
	t_pipex	list;
	size_t	i;

	if (ac != 5)
		return (write(2, "Error: wrong number of arguments\n", 34), 1);
	list.infile = open(av[1], O_RDONLY);
	list.outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	list.path = get_env_path(env);
	list.cmd = get_cmd(av, ac);
	list.cmd_path = get_cmd_path(list.path, list.cmd);
	ft_printf("path: %s\n", list.path);
	print_tab(list.cmd);
	print_tab(list.cmd_path);
	first_fork(&list);
	mid_fork(&list, ac);
}
