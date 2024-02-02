/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 10:21:20 by vzuccare          #+#    #+#             */
/*   Updated: 2024/02/02 16:08:41 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_tab(char **tab)
{
	size_t	i;

	i = -1;
	while (tab[++i])
		printf("%s\n", tab[i]);
}

char	*can_acess(char *cmd, char **cmd_path)
{
	size_t	i;
	char	*tmp;

	i = -1;
	while (cmd_path[++i])
	{
		tmp = ft_strjoin(cmd_path[i], "/");
		if (!tmp)
			return (NULL);
		tmp = ft_strjoin(tmp, cmd);
		if (!tmp)
			return (NULL);
		if (access(tmp, F_OK) == 0)
		{
			tmp = ft_strjoin(".", tmp);
			printf("cmd found: %s\n", tmp);
			return (tmp);
		}
		free(tmp);
	}
	return (NULL);
}

int	parse_env(char **env, char **av, t_pipex *list)
{
	size_t	i;

	i = 0;
	(void) av;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			list->path = ft_strdup(env[i] + 5);
			if (!list->path)
				return (1);
			break ;
		}
		i++;
	}
	list->cmd_path = ft_split(list->path, ':');
	if (!list->cmd_path)
		return (1);
	print_tab(list->cmd_path);
	return (0);
}
