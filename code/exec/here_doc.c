/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 17:09:04 by vincent           #+#    #+#             */
/*   Updated: 2024/05/21 15:47:33 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char *collect_heredoc_input(char *delimiter)
{
	char *line;
	char *tmp;
	char *tmp2;

	tmp = ft_strdup("");
	if (!tmp)
		ft_exit_error(NULL, 1);
	while (1)
	{
		line = get_next_line(0);
		if (!line || !ft_strncmp(line, delimiter, ft_strlen(delimiter)))
		{
			if (!line)
			{
				ft_printf_fd(2, "minishell: syntax error\n");
				free(tmp);
				ft_exit_error(NULL, 1);
			}
			free(line);
			break;
		}
		tmp2 = ft_strjoin(tmp, line);
		free(tmp);
		tmp = tmp2;
		free(line);
	}
	return (tmp);
}

int here_doc(t_pipex *pipex, char *infile_name)
{
	int pipefd[2];
	char *input;

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		ft_exit_error(pipex->env, 1);
	}
	input = collect_heredoc_input(infile_name);
	if (!input)
		ft_exit_error(pipex->env, 1);
	write(pipefd[1], input, ft_strlen(input));
	close(pipefd[1]);
	free(input);

	return pipefd[0];
}
