/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesies.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 00:20:39 by vincent           #+#    #+#             */
/*   Updated: 2024/05/23 12:22:16 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/* //check if there is any parentheses in the command and delete them
static void	delete_parentheses(t_pipex *pipex)
{
	int	i;
	int	j;
	int	start[2];

	start[0] = -1;
	start[1] = -1;
	i = -1;
	while (pipex->cmd[++i] != NULL)
	{
		j = -1;
		while (pipex->cmd[i][++j] != '\0')
		{
			if (pipex->cmd[i][j] == '(')
			{
				start[0] = i;
				start[1] = j;
			}
		}
	}
}

static	int count_len(char **cmd, int start[2], int end[2])
{
	int	i;
	int	len;

	i = start[0];
	len = 0;
	while (i < end[0])
	{
		if (i == start[0])
			len += ft_strlen(cmd[i]) - start[1];
		else if (i == end[0])
			len += end[1];
		else
			len += ft_strlen(cmd[i]);
		i++;
	}
	return (len);
}
{

}
{
	int	i;
	int	len;

	i = -1;
	len = 0;
	while (cmd[++i] != NULL)
		len++;
	return (len);
}
 */

void	check_for_parentheses(t_pipex *pipex)
{
	(void) pipex;
}