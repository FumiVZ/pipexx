/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_outfile.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 17:36:24 by vzuccare          #+#    #+#             */
/*   Updated: 2024/06/12 18:13:45 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	open_outfiles(t_pipex *pipex, char *cmd, char *file)
{
	int		fd;
	char	**tmp;

	(void)pipex;
	tmp = malloc(sizeof(char *) * 2);
	if (!tmp)
		return (-1);
	tmp[0] = ft_strdup(file);
	if (!tmp[0])
		return (-1);
	tmp[1] = NULL;
	tmp = pattern_matching(tmp, pipex->env->envp, pipex->env);
	quote_removal(tmp);
	if (ft_strstrlen(tmp) != 1)
	{
		ft_printf_fd(2, "pipex: ambiguous redirect\n");
		free_split(tmp, ft_strstrlen(tmp));
		return (-1);
	}
	if (chre(cmd, ">"))
		fd = open(tmp[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(tmp[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
	free_split(tmp, ft_strstrlen(tmp));
	return (fd);
}

void	error_outfile(t_pipex *pipex, t_cmd *cmds, char *file)
{
	int	j;

	if (errno != 0)
		msg_error_outfile(ERR_FILE, *pipex, file);
	pipex->env->status = 1;
	j = -1;
	while (cmds->outfiles_name[++j])
	{
		if (cmds->outfiles[j] > 0)
			close(cmds->outfiles[j]);
		cmds->outfiles[j] = -1;
		free(cmds->outfiles_name[j]);
		cmds->outfiles_name[j] = NULL;
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
				quote_rm_world(cmd[i + 1], NULL);
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
		{
			free(cmds->outfiles);
			msg_error(ERR_MALLOC, pipex);
		}
		cmds->outfiles_name[j] = NULL;
	}
}
