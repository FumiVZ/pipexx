/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 10:33:12 by vzuccare          #+#    #+#             */
/*   Updated: 2024/02/21 16:26:05 by vzuccare         ###   ########lyon.fr   */
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
		dup2(pipex->infile, 0);
		dup2(pipex->fd[1], 1);
		close(pipex->fd[0]);
		close(pipex->infile);
		close(pipex->outfile);
		if (!(ft_strncmp(pipex->cmd[0], "/", 1) == 0 && \
			ft_strlen(pipex->cmd[0]) == 1))
			execve(pipex->cmd[0], pipex->args[0], pipex->path);
		else
		{
			ft_printf(2, "pipex: command not found: %s\n", av[2]);
			free_tab(pipex->path);
			free(pipex->cmd[0]);
			free_tab(pipex->args[0]);
			exit(127);
		}
	}
}

void	parrent_process(t_pipex *pipex, char **av)
{
	init_exec(pipex, av, 1);
	pipex->pid2 = fork();
	if (pipex->pid2 < 0)
		ft_error(strerror(errno), pipex, NULL);
	if (pipex->pid2 == 0)
	{
		dup2(pipex->fd[0], 0);
		dup2(pipex->outfile, 1);
		close(pipex->fd[1]);
		close(pipex->infile);
		close(pipex->outfile);
		if (ft_strncmp(pipex->cmd[1], "/", 1) == 0 && \
			ft_strlen(pipex->cmd[1]) == 1)
		{
			free_tab(pipex->path);
			free(pipex->cmd[1]);
			free_tab(pipex->args[1]);
			ft_printf(2, "pipex: command not found: %s\n", av[3]);
			exit(127);
		}
		else
			execve(pipex->cmd[1], pipex->args[1], pipex->path);
	}
	free(pipex->cmd[1]);
	free_tab(pipex->args[1]);
}

int	main(int ac, char **av, char **env)
{
	t_pipex	pipex;

	pipex_init(&pipex);
	if (ac != 5)
		return (write(2, "Error: wrong number of arguments\n", 34), 1);
	if (pipe(pipex.fd) == -1)
		ft_error(strerror(errno), &pipex, NULL);
	pipex.outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	pipex.infile = open(av[1], O_RDONLY);
	pipex.path = ft_split(get_env_path(env), ':');
	if (!pipex.infile || !pipex.outfile || !pipex.path)
		ft_error(strerror(errno), &pipex, NULL);
	child_process(&pipex, av);
	free(pipex.cmd[0]);
	free_tab(pipex.args[0]);
	parrent_process(&pipex, av);
	if (pipex.pid1 == 0)
		waitpid(pipex.pid1, NULL, 0);
	if (pipex.pid2 == 0)
		waitpid(pipex.pid2, NULL, 0);
	free_tab(pipex.path);
	close(pipex.infile);
	close(pipex.outfile);
	close(pipex.fd[0]);
	close(pipex.fd[1]);
}
