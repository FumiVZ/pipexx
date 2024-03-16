/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 14:52:58 by machrist          #+#    #+#             */
/*   Updated: 2024/03/16 14:58:42 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

size_t	len_cmd(char **cmd)
{
	size_t	i;

	i = 0;
	while (cmd[i] && !is_sep(cmd[i]))
		i++;
	return (i);
}

char	**sep_case(char **cmds)
{
	size_t	j;
	size_t	len;
	char	**cmd;

	if (is_sep(*cmds) <= 4)
	{
		cmd = malloc(sizeof(char *) * 3);
		cmd[0] = ft_strdup(*cmds);
		cmd[1] = ft_strdup(*cmds + 1);
		cmd[2] = NULL;
		return (cmd);
	}
	len = len_cmd(cmds) + 1;
	cmd = malloc(sizeof(char *) * (len + 1));
	cmd[0] = ft_strdup(*cmds);
	j = 1;
	while (cmds[j] && !is_sep(cmds[j]))
	{
		cmd[j] = ft_strdup(cmds[j]);
		j++;
	}
	cmd[len] = NULL;
	return (cmd);
}

char	**create_cmd(char **cmds)
{
	size_t	j;
	size_t	len;
	char	**cmd;

	if (!cmds)
		return (NULL);
	if (!*cmds)
		return (NULL);
	if (!**cmds)
		return (NULL);
	j = 0;
	if (is_sep(cmds[j]))
		return (sep_case(cmds));
	len = len_cmd(cmds);
	cmd = malloc(sizeof(char *) * (len + 1));
	if (!cmd)
		exit(1);
	while (cmds[j] && !is_sep(cmds[j]))
	{
		cmd[j] = ft_strdup(cmds[j]);
		j++;
	}
	cmd[len] = NULL;
	return (cmd);
}