/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincent <vincent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 17:09:04 by vincent           #+#    #+#             */
/*   Updated: 2024/05/15 04:23:04 by vincent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/* int	here_doc(t_pipex *pipex, t_cmd *cmds, char **cmd)
{
	int		i;
	int		fd;
	char	*line;

	i = -1;
	fd = 0;
	while (!chre(line, cmds->infiles_name[]))
	{
		get_next_line(&line);
		if (!line)
			break ;
		if (fd)
			close(fd);
		free(line);
		break ;
	}
	ft_putendl_fd(line, fd);
	free(line);
	close(fd);
	j++;
	return (fd);
} */