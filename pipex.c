/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 10:33:12 by vzuccare          #+#    #+#             */
/*   Updated: 2024/03/04 17:42:35 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	init_exec(pipex, av, 0);
	pipex->pid1 = fork();
	if (pipex->pid1 < 0)
		ft_error(strerror(errno), pipex, NULL);
	if (pipex->pid1 == 0)
	{
		pipex->infile = open(av[1], O_RDONLY);
		if (pipex->infile == -1)
			ft_error(strerror(errno), pipex, av[1]);
		dup2(pipex->infile, 0);
		dup2(pipex->fd[1], 1);
		close(pipex->fd[0]);
		close(pipex->fd[1]);
		close(pipex->infile);
		if (!(pipex->cmd[0] && access(pipex->cmd[0], X_OK) == 0))
		{
			ft_printf(2, "pipex: command not found: %s\n", av[2]);
			free_child(pipex);
			exit(127);
		}
		execve(pipex->cmd[0], pipex->args[0], pipex->path);
		free_child(pipex);
		exit(1);
	}
}

void	child2_process(t_pipex *pipex, char **av)
{
	init_exec(pipex, av, 1);
	pipex->pid2 = fork();
	if (pipex->pid2 < 0)
		ft_error(strerror(errno), pipex, NULL);
	if (pipex->pid2 == 0)
	{
		pipex->outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (pipex->outfile == -1)
			ft_error(strerror(errno), pipex, av[4]);
		dup2(pipex->fd[0], 0);
		dup2(pipex->outfile, 1);
		close(pipex->fd[0]);
		close(pipex->fd[1]);
		close(pipex->outfile);
		if (!(pipex->cmd[1] && access(pipex->cmd[1], X_OK) == 0))
		{
			ft_printf(2, "pipex: command not found: %s\n", av[3]);
			free_child2(pipex);
			exit(127);
		}
		execve(pipex->cmd[1], pipex->args[1], pipex->path);
		free_child2(pipex);
		exit(1);
	}
}

int	main(int ac, char **av, char **env)
{
	t_pipex	pipex;
	int		status;

	status = 0;
	pipex_init(&pipex);
	if (ac != 5)
		return (write(2, "Error: wrong number of arguments\n", 34), 1);
	if (pipe(pipex.fd) == -1)
		ft_error(strerror(errno), &pipex, NULL);
	pipex.path = ft_split(get_env_path(env), ':');
	if (!pipex.path)
		ft_error(strerror(errno), &pipex, NULL);
	child_process(&pipex, av);
	child2_process(&pipex, av);
	close(pipex.fd[0]);
	close(pipex.fd[1]);
	close(pipex.infile);
	close(pipex.outfile);
	waitpid(pipex.pid1, &status, 0);
	waitpid(pipex.pid2, &status, 0);
	free_child2(&pipex);
	if (WIFEXITED(status))
		return (status);
}
head -n -1 original_file.txt > new_file.txt