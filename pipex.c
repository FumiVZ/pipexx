/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 10:33:12 by vzuccare          #+#    #+#             */
/*   Updated: 2024/02/12 16:37:00 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_tab(char **tab)
{
	size_t	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

void	free_pipex(t_pipex pipex)
{
	size_t	i;

	i = -1;
	if (pipex.path)
	{
		while (pipex.path[++i])
			if (pipex.path[i])
				free(pipex.path[i]);
		if (pipex.path)
			free(pipex.path);
	}
}

char	*first_word(char *str)
{
	size_t	i;
	char	*word;

	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	word = malloc(sizeof(char) * (i + 1));
	if (!word)
		return (NULL);
	i = -1;
	while (str[++i] && str[i] != ' ')
		word[i] = str[i];
	word[i] = 0;
	return (word);
}

void	child_process(t_pipex *pipex, char **av)
{
	pipex->pid1 = fork();
	pipex->cmd[0] = get_cmd_path(pipex->path, first_word(av[2]));
	pipex->args[0] = ft_split(av[2], ' ');
	if (pipex->pid1 < 0)
		ft_printf(1, "ERROR");
	if (pipex->pid1 == 0)
	{
		dup2(pipex->infile, 0);
		dup2(pipex->fd[1], 1);
		close(pipex->fd[0]);
		close(pipex->infile);
		close(pipex->outfile);
		execve(pipex->cmd[0], pipex->args[0], pipex->path);
	}
	free(pipex->cmd[0]);
	free_tab(pipex->args[0]);
}

void	parrent_process(t_pipex *pipex, char **av)
{ 
	pipex->pid2 = fork();
	pipex->cmd[1] = get_cmd_path(pipex->path, first_word(av[3]));
	pipex->args[1] = ft_split(av[3], ' ');
	if (pipex->pid2 < 0)
		ft_printf(1, "ERROR");
	if (pipex->pid2 == 0)
	{
		dup2(pipex->fd[0], 0);
		dup2(pipex->outfile, 1);
		close(pipex->fd[1]);
		close(pipex->infile);
		close(pipex->outfile);
		execve(pipex->cmd[1], pipex->args[1], pipex->path);
	}
	free(pipex->cmd[1]);
	free_tab(pipex->args[1]);
}

int	main(int ac, char **av, char **env)
{
	t_pipex	pipex;

	if (ac != 5)
		return (write(2, "Error: wrong number of arguments\n", 34), 1);
	if (pipe(pipex.fd) == -1)
		ft_printf(1, "ERROR");
	pipex.infile = open(av[1], O_RDONLY);
	pipex.outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	pipex.path = ft_split(get_env_path(env), ':');
	child_process(&pipex, av);
	parrent_process(&pipex, av);
	free_pipex(pipex);
	close(pipex.infile);
	close(pipex.outfile);
	close(pipex.fd[0]);
	close(pipex.fd[1]);
}
