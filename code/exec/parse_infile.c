/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_infile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 17:27:05 by vzuccare          #+#    #+#             */
/*   Updated: 2024/05/25 17:38:54 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	malloc_infiles(t_pipex *pipex, t_cmd *cmds, char **cmd)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (cmd[++i] && !(chre(cmd[i], "&&") || chre(cmd[i], "||")
			|| chre(cmd[i], "|")))
		if (chre(cmd[i], "<") || chre(cmd[i], "<<"))
			j++;
	if (j)
	{
		cmds->infiles = malloc(sizeof(int) * (j + 1));
		if (!cmds->infiles)
			msg_error(ERR_MALLOC, pipex);
		else
			cmds->infiles_name = malloc(sizeof(char *) * (j + 1));
		if (!cmds->infiles_name)
			msg_error(ERR_MALLOC, pipex);
		cmds->infiles_name[j] = NULL;
	}
}

int	open_infiles(t_pipex *pipex, char *cmd, char *file, char *infile_name)
{
	int		fd;
	char	*tmp;

	tmp = NULL;
	if (ft_strncmp(cmd, "<<", 2))
	{
		file = quote_rm_world(file, tmp);
		fd = open(file, O_RDONLY);
	}
	else
		fd = here_doc(pipex, infile_name);
	return (fd);
}

void	error_infile(t_pipex *pipex, t_cmd *cmds, char *file)
{
	int	j;

	msg_error_infile(ERR_FILE, *pipex, file);
	pipex->env->status = 1;
	j = -1;
	while (cmds->infiles[++j] != -1)
	{
		close(cmds->infiles[j]);
		free(cmds->infiles_name[j]);
	}
	free(cmds->infiles);
	free(cmds->infiles_name);
	cmds->infiles = NULL;
	cmds->infiles_name = NULL;
	cmds->exec = 0;
}

void	get_infiles(t_pipex *pipex, char **cmd, t_cmd *cmds)
{
	int	i;
	int	j;

	malloc_infiles(pipex, cmds, cmd);
	if (!cmds->infiles)
		return ;
	i = -1;
	j = 0;
	while (cmd[++i] && !(chre(cmd[i], "&&") || chre(cmd[i], "||")
			|| chre(cmd[i], "|")))
	{
		if (chre(cmd[i], "<") || chre(cmd[i], "<<"))
		{
			cmds->infiles_name[j] = quote_rm_world(ft_strdup(cmd[i + 1]), NULL);
			cmds->infiles[j] = open_infiles(pipex, cmd[i], cmd[i + 1],
					cmds->infiles_name[j]);
			if (cmds->infiles[j] < 0)
			{
				error_infile(pipex, cmds, cmds->infiles_name[j]);
				break ;
			}
			j++;
		}
		cmds->infiles[j] = -1;
	}
}
