/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincent <vincent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 22:04:48 by vincent           #+#    #+#             */
/*   Updated: 2024/05/20 02:32:40 by vincent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <minishell.h>

//function to compare two string char by char and by lenght
int	chre(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		if (s1[i] == s2[i])
			i++;
		else
			return (0);
	}
	if (ft_strlen(s1) == ft_strlen(s2))
		return (1);
	return (0);
}

static void	malloc_infiles(t_pipex *pipex, t_cmd *cmds, char **cmd)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (cmd[++i] && !(chre(cmd[i], "&&") \
		|| chre(cmd[i], "||") || chre(cmd[i], "|")))
		if (chre(cmd[i], "<") || chre(cmd[i], "<<"))
			j++;
	if (j)
	{
		cmds->infiles = malloc(sizeof(int) * (j + 1));
		if (!cmds->infiles)
			msg_error(ERR_MALLOC, pipex);
		cmds->infiles_name = malloc(sizeof(char *) * (j + 1));
		if (!cmds->infiles_name)
			msg_error(ERR_MALLOC, pipex);
		cmds->infiles_name[j] = NULL;
	}
}

static void	malloc_outfiles(t_pipex *pipex, t_cmd *cmds, char **cmd)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (cmd[++i] && !(chre(cmd[i], "&&") \
		|| chre(cmd[i], "||") || chre(cmd[i], "|")))
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

int		open_infiles(t_pipex *pipex, char *cmd, char *file, char *infile_name)
{
	int	fd;

	if (ft_strncmp(cmd, "<<", 2))
		fd = open(file, O_RDONLY);
	else
	{
		ft_printf_fd(2, "here_doc\n");
		fd = here_doc(pipex, infile_name);
	}
	return (fd);
}

static void	get_infiles(t_pipex *pipex, char **cmd, t_cmd *cmds)
{
	int	i;
	int	j;

	malloc_infiles(pipex, cmds, cmd);
	if (!cmds->infiles)
		return ;
	i = -1;
	j = 0;
	while (cmd[++i] && !(chre(cmd[i], "&&") \
		|| chre(cmd[i], "||") || chre(cmd[i], "|")))
	{
		if (chre(cmd[i], "<") || chre(cmd[i], "<<"))
		{
			cmds->infiles_name[j] = ft_strdup(cmd[i + 1]);
			cmds->infiles[j] = open_infiles(pipex, cmd[i], cmd[i + 1], cmds->infiles_name[j]);
			if (cmds->infiles[j] < 0)
			{
				msg_error_infile(ERR_FILE, *pipex, cmds->infiles_name[j]);
				pipex->env->status = 1;
			}
			j++;
		}
		cmds->infiles[j] = -1;
	}
}

int		open_outfiles(t_pipex *pipex, char *cmd, char *file)
{
	int	fd;

	(void)pipex;
	if (chre(cmd, ">"))
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	return (fd);
}

static void	get_outfiles(t_pipex *pipex, char **cmd, t_cmd *cmds)
{
	int	i;
	int	j;

	malloc_outfiles(pipex, cmds, cmd);
	if (!cmds->outfiles)
		return ;
	i = -1;
	j = 0;
	while (cmd[++i] && !(chre(cmd[i], "&&") \
		|| chre(cmd[i], "||") || chre(cmd[i], "|")))
	{
		if (chre(cmd[i], ">") || chre(cmd[i], ">>"))
		{
			cmds->outfiles_name[j] = ft_strdup(cmd[i + 1]);
			cmds->outfiles[j] = open_outfiles(pipex, cmd[i], cmd[i + 1]);
			if (cmds->outfiles[j] < 0)
			{
				msg_error_outfile(ERR_FILE, *pipex, cmds->infiles_name[j]);
				pipex->env->status = 1;
			}
			j++;
		}
		cmds->outfiles[j] = -1; 
	}
}

char	**malloc_args(t_pipex *pipex, char **cmd)
{
	int		i;
	int		j;
	char	**args;

	i = -1;
	j = 0;
	while (cmd[++i] && !(chre(cmd[i], "||") \
		|| chre(cmd[i], "&&") || chre(cmd[i], "|")))
	{
		while (cmd[i] && (chre(cmd[i], "<") \
			|| chre(cmd[i], "<<") || chre(cmd[i], ">>") || chre(cmd[i], ">")))
			i += 2;
		if (cmd[i] && !(chre(cmd[i], "||") \
			|| chre(cmd[i], "&&") || chre(cmd[i], "|")))
			j++;
		if (!cmd[i] || (chre(cmd[i], "||") \
			|| chre(cmd[i], "&&") || chre(cmd[i], "|")))
			break ;
	}
	args = malloc(sizeof(char *) * (j + 1));
	if (!args)
		msg_error(ERR_MALLOC, pipex);
	return (args);
}

char **get_args(t_pipex *pipex, char **cmd)
{
	int		i;
	int		j;
	char	**args;

	args = malloc_args(pipex, cmd);
	i = -1;
	j = 0;
	while (cmd[++i] && !(chre(cmd[i], "||") \
		|| chre(cmd[i], "&&") || chre(cmd[i], "|")))
	{
		while (cmd[i] && (chre(cmd[i], "<") \
			|| chre(cmd[i], "<<") || chre(cmd[i], ">>") || chre(cmd[i], ">")))
			i += 2;
		if (cmd[i] && !(chre(cmd[i], "||") \
			|| chre(cmd[i], "&&") || chre(cmd[i], "|")))
			args[j++] = ft_strdup(cmd[i]);
		if (!cmd[i] || (chre(cmd[i], "||") \
			|| chre(cmd[i], "&&") || chre(cmd[i], "|")))
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
	while (pipex->cmd[pipex->i] && !(chre(pipex->cmd[pipex->i], "&&") || \
		chre(pipex->cmd[pipex->i], "||")) && !chre(pipex->cmd[pipex->i], "|"))
		pipex->i++;
	if (pipex->cmd[pipex->i] && chre(pipex->cmd[pipex->i], "|"))
		pipex->i++;
}

bool	delete_parenthesies(t_pipex *pipex)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (pipex->cmd[i])
	{
		if (pipex->cmd[i][0] == '(')
		{
			
		}
		if (j < 0)
			return (false);
		i++;
	}
	if (j)
		return (false);
	return (true);
}


void	parse_cmd(t_pipex *pipex, t_cmd *cmds)
{
		t_cmd   *tmp;

		if (!cmds)
				msg_error(ERR_MALLOC, pipex);
		list_init(cmds);
		pipex->cmd_nmbs = 0;
/*      check_for_parentheses(pipex); */
		cmds->args = get_args(pipex, &pipex->cmd[pipex->i]);
		get_infiles(pipex, &pipex->cmd[pipex->i], cmds);
		get_outfiles(pipex, &pipex->cmd[pipex->i], cmds);
		while (pipex->cmd[pipex->i] && !(chre(pipex->cmd[pipex->i], "&&") || \
				chre(pipex->cmd[pipex->i], "||")) && !chre(pipex->cmd[pipex->i], "|"))
				pipex->i++;
		if (!pipex->cmd[pipex->i] || (chre(pipex->cmd[pipex->i], "||") || chre(pipex->cmd[pipex->i], "&&")))
		{
				tmp = cmds;
				while (cmds->next)
						cmds = cmds->next;
				pipex->nb_pipes = 2 * (pipex->cmd_nmbs - 1);
				cmds = tmp;
				printf("cmd_nmbs = %d\n", pipex->cmd_nmbs);
				pipex->pid = malloc(sizeof(pid_t) * (pipex->cmd_nmbs));
				return ;
		}
		if (pipex->cmd[pipex->i])
				pipex->i++;
		while (pipex->cmd[pipex->i] && !(chre(pipex->cmd[pipex->i], "&&") \
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
