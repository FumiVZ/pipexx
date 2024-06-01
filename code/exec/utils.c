/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincent <vincent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 16:27:22 by vzuccare          #+#    #+#             */
/*   Updated: 2024/06/01 15:12:29 by vincent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

int	count_pipes(t_pipex *pipex)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (pipex->cmd[j])
	{
		if (ft_strncmp(pipex->cmd[j], "|", 1) == 0)
			i++;
		if (ft_strncmp(pipex->cmd[j], ">", 1) == 0)
			i++;
		if (ft_strncmp(pipex->cmd[j], ">>", 2) == 0)
			i++;
		if (ft_strncmp(pipex->cmd[j], "<", 1) == 0)
			i++;
		j++;
	}
	return (i);
}

char	*remove_quotes(char *str)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	new = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!new)
		return (NULL);
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '\"')
		{
			new[j] = str[i];
			j++;
		}
		i++;
	}
	new[j] = 0;
	return (new);
}

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

bool	ft_builtins(t_env *env, t_pipex *pipex, char **args)
{
	if (!args || !args[0])
		return (0);
	if (!ft_strncmp(args[0], "echo", 5))
		ft_echo(env, args);
	else if (!ft_strncmp(args[0], "exit", 5))
		ft_exit(env, pipex, args);
	else if (!ft_strncmp(args[0], "cd", 3))
		ft_cd(env, args, pipex);
	else if (!ft_strncmp(args[0], "env", 4))
		ft_env(env);
	else if (!ft_strncmp(args[0], "pwd", 4))
		ft_pwd(env);
	else if (!ft_strncmp(args[0], "export", 7))
		ft_export(env, args, pipex);
	else if (!ft_strncmp(args[0], "unset", 6))
		ft_unset(env, args);
	else
		return (0);
	return (1);
}

int	is_builtin(char **args)
{
	if (!args || !args[0])
		return (0);
	if (!ft_strncmp(args[0], "echo", 5))
		return (1);
	else if (!ft_strncmp(args[0], "exit", 5))
		return (1);
	else if (!ft_strncmp(args[0], "cd", 3))
		return (1);
	else if (!ft_strncmp(args[0], "env", 4))
		return (1);
	else if (!ft_strncmp(args[0], "pwd", 4))
		return (1);
	else if (!ft_strncmp(args[0], "export", 7))
		return (1);
	else if (!ft_strncmp(args[0], "unset", 6))
		return (1);
	else
		return (0);
}