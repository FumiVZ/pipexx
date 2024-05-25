/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_outfile.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 17:36:24 by vzuccare          #+#    #+#             */
/*   Updated: 2024/05/25 17:39:59 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	open_outfiles(t_pipex *pipex, char *cmd, char *file)
{
	int		fd;
	char	*tmp;

	(void)pipex;
	tmp = NULL;
	file = quote_rm_world(file, tmp);
	if (chre(cmd, ">"))
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	return (fd);
}

void	error_outfile(t_pipex *pipex, t_cmd *cmds, char *file)
{
	int	j;

	msg_error_outfile(ERR_FILE, *pipex, file);
	pipex->env->status = 1;
	j = -1;
	while (cmds->outfiles_name[++j])
	{
		close(cmds->outfiles[j]);
		free(cmds->outfiles_name[j]);
	}
	free(cmds->outfiles);
	free(cmds->outfiles_name);
	cmds->outfiles = NULL;
	cmds->outfiles_name = NULL;
	cmds->exec = 0;
}

void	get_outfiles(t_pipex *pipex, char **cmd, t_cmd *cmds)
{
	int	i;
	int	j;

	malloc_outfiles(pipex, cmds, cmd);
	if (!cmds->outfiles)
		return ;
	i = -1;
	j = 0;
	while (cmd[++i] && !(chre(cmd[i], "&&") || chre(cmd[i], "||")
			|| chre(cmd[i], "|")))
	{
		if (chre(cmd[i], ">") || chre(cmd[i], ">>"))
		{
			cmds->outfiles_name[j] = \
				quote_rm_world(ft_strdup(cmd[i + 1]), NULL);
			cmds->outfiles[j] = open_outfiles(pipex, cmd[i], cmd[i + 1]);
			if (cmds->outfiles[j] < 0)
			{
				error_outfile(pipex, cmds, cmds->outfiles_name[j]);
				break ;
			}
			j++;
		}
		cmds->outfiles[j] = -1;
	}
}

void	malloc_outfiles(t_pipex *pipex, t_cmd *cmds, char **cmd)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (cmd[++i] && !(chre(cmd[i], "&&") || chre(cmd[i], "||")
			|| chre(cmd[i], "|")))
		if (chre(cmd[i], ">") || chre(cmd[i], ">>"))
			j++;
	if (j)
	{
		cmds->outfiles = malloc(sizeof(int) * (j + 1));
		if (!cmds->outfiles)
			msg_error(ERR_MALLOC, pipex);
		cmds->outfiles_name = malloc(sizeof(char *) * (j + 1));
		if (!cmds->outfiles_name)
			msg_error(ERR_MALLOC, pipex);
		cmds->outfiles_name[j] = NULL;
	}
}