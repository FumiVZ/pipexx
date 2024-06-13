/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 17:09:04 by vincent           #+#    #+#             */
/*   Updated: 2024/06/13 18:42:43 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

global pid_t	g_child_pid;

static char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*tmp;

	tmp = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (tmp);
}

char	*collect_heredoc_input(char *delimiter)
{
	char	*line;
	char	*tmp;

	tmp = ft_strdup("");
	if (!tmp)
		ft_exit_error(NULL, 1);
	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strncmp(line, delimiter, ft_strlen(delimiter)))
		{
			if (!line)
			{
				ft_printf_fd(2, "minishell: syntax error\n");
				free(tmp);
				ft_exit_error(NULL, 1);
			}
			free(line);
			break ;
		}
		tmp = ft_strjoin_free(tmp, line);
		if (!tmp)
			ft_exit_error(NULL, 1);
	}
	return (tmp);
}

int	here_doc(t_pipex *pipex, char *infile_name)
{
	int					pipefd[2];
	char				*input;
	pid_t				pid;

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		ft_exit_error(pipex->env, 1);
	}
	ft_printf_fd(2, "TEST\n");
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		ft_exit_error(pipex->env, 1);
	}
	if (pid == 0)
	{
		g_child_pid = getpid();
		input = collect_heredoc_input(infile_name);
		if (!input)
			ft_exit_error(pipex->env, 1);
		write(pipefd[1], input, ft_strlen(input));
		close(pipefd[1]);
		close(pipefd[0]);
		free(input);
		exit(0);
	}
	waitpid(pid, &pipex->env->status, 0);
	close(pipefd[1]);
	close(pipefd[0]);
	return (pipefd[0]);
}
