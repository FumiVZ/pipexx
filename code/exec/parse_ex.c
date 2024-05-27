/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincent <vincent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 22:04:48 by vincent           #+#    #+#             */
/*   Updated: 2024/05/27 17:35:09 by vincent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// function to compare two string char by char and by lenght

char	**malloc_args(t_pipex *pipex, char **cmd)
{
	int		i;
	int		j;
	char	**args;

	i = -1;
	j = 0;
	while (cmd[++i] && !(chre(cmd[i], "||") || chre(cmd[i], "&&")
			|| chre(cmd[i], "|")))
	{
		while (cmd[i] && (chre(cmd[i], "<") || chre(cmd[i], "<<")
				|| chre(cmd[i], ">>") || chre(cmd[i], ">")))
			i += 2;
		if (cmd[i] && !(chre(cmd[i], "||") || chre(cmd[i], "&&") || chre(cmd[i],
					"|")))
			j++;
		if (!cmd[i] || (chre(cmd[i], "||") || chre(cmd[i], "&&") || chre(cmd[i],
					"|")))
			break ;
	}
	args = malloc(sizeof(char *) * (j + 1));
	if (!args)
		msg_error(ERR_MALLOC, pipex);
	return (args);
}

char	**get_args(t_pipex *pipex, char **cmd)
{
	int		i;
	int		j;
	char	**args;

	args = malloc_args(pipex, cmd);
	i = -1;
	j = 0;
	while (cmd[++i] && !(chre(cmd[i], "||") || chre(cmd[i], "&&")
			|| chre(cmd[i], "|")))
	{
		while (cmd[i] && (chre(cmd[i], "<") || chre(cmd[i], "<<")
				|| chre(cmd[i], ">>") || chre(cmd[i], ">")))
			i += 2;
		if (cmd[i] && !(chre(cmd[i], "||") || chre(cmd[i], "&&") || chre(cmd[i],
					"|")))
			args[j++] = ft_strdup(cmd[i]);
		if (!cmd[i] || (chre(cmd[i], "||") || chre(cmd[i], "&&") || chre(cmd[i],
					"|")))
			break ;
	}
	args[j] = NULL;
	if (args)
		pipex->cmd_nmbs++;
	return (args);
}

void	create_new_nodes(t_pipex *pipex, t_cmd *cmds)
{
	t_cmd	*tmp;

	while (cmds->next)
		cmds = cmds->next;
	tmp = malloc(sizeof(t_cmd));
	list_init(tmp);
	if (!tmp)
		msg_error(ERR_MALLOC, pipex);
	tmp->args = get_args(pipex, &pipex->cmd[pipex->i]);
	tmp->pipeid = cmds->pipeid + 1;
	get_infiles(pipex, &pipex->cmd[pipex->i], tmp);
	if (pipex->env->status == 0)
		get_outfiles(pipex, &pipex->cmd[pipex->i], tmp);
	tmp->next = NULL;
	cmds->next = tmp;
	while (pipex->cmd[pipex->i] && !(chre(pipex->cmd[pipex->i], "&&")
			|| chre(pipex->cmd[pipex->i], "||")) && !chre(pipex->cmd[pipex->i],
			"|"))
		pipex->i++;
	if (pipex->cmd[pipex->i] && chre(pipex->cmd[pipex->i], "|"))
		pipex->i++;
}

void	first_node(t_pipex *pipex, t_cmd *cmds)
{
	t_cmd	*tmp;

	list_init(cmds);
	pipex->cmd_nmbs = 0;
	check_for_parentheses(pipex);
	cmds->args = get_args(pipex, &pipex->cmd[pipex->i]);
	get_infiles(pipex, &pipex->cmd[pipex->i], cmds);
	get_outfiles(pipex, &pipex->cmd[pipex->i], cmds);
	while (pipex->cmd[pipex->i] && !(chre(pipex->cmd[pipex->i], "&&")
			|| chre(pipex->cmd[pipex->i], "||")) && !chre(pipex->cmd[pipex->i],
			"|"))
		pipex->i++;
	if (!pipex->cmd[pipex->i] || (chre(pipex->cmd[pipex->i], "||")
			|| chre(pipex->cmd[pipex->i], "&&")))
	{
		tmp = cmds;
		while (cmds->next)
			cmds = cmds->next;
		pipex->nb_pipes = 2 * (pipex->cmd_nmbs - 1);
		cmds = tmp;
		return ;
	}
}

void	parse_cmd(t_pipex *pipex, t_cmd *cmds)
{
	t_cmd	*tmp;

	if (!cmds)
		msg_error(ERR_MALLOC, pipex);
	first_node(pipex, cmds);
	if (pipex->cmd[pipex->i])
		pipex->i++;
	while (pipex->cmd[pipex->i] && !(chre(pipex->cmd[pipex->i], "&&")
			|| chre(pipex->cmd[pipex->i], "||")))
		create_new_nodes(pipex, cmds);
	tmp = cmds;
	while (cmds->next)
		cmds = cmds->next;
	pipex->nb_pipes = 2 * (pipex->cmd_nmbs - 1);
	cmds = tmp;
	pipex->pid = malloc(sizeof(pid_t) * (pipex->cmd_nmbs));
	if (!pipex->pid)
		msg_error(ERR_MALLOC, pipex);
}
