/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:47:33 by machrist          #+#    #+#             */
/*   Updated: 2024/05/21 17:08:55 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	**ft_unset_envp(char **envp, char **cmd)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	**new;

	i = 0;
	j = 0;
	new = malloc(sizeof(char *) * (ft_strstrlen(envp) + 1 - ft_strstrlen(cmd)));
	if (!new)
		return (free(cmd), NULL);
	while (envp[i])
	{
		k = 0;
		while (cmd[k])
		{
			if (!ft_strncmp(envp[i], cmd[k], ft_strlen(cmd[k]))
				&& envp[i][ft_strlen(cmd[k])] == '=')
				free(envp[i++]);
			k++;
		}
		if (envp[i])
			new[j++] = envp[i++];
	}
	new[j] = NULL;
	return (new);
}

static char	**ft_clean_cmd(char **envp, char **cmd)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	**new;

	new = malloc(sizeof(char *) * (ft_strstrlen(cmd) + 1));
	if (!new)
		return (NULL);
	i = 0;
	k = 0;
	while (envp[i])
	{
		j = 0;
		while (cmd[j])
		{
			if (!ft_strncmp(envp[i], cmd[j], ft_strlen(cmd[j]))
				&& envp[i][ft_strlen(cmd[j])] == '=')
				new[k++] = cmd[j];
			j++;
		}
		i++;
	}
	new[k] = NULL;
	return (new);
}

void	ft_unset(t_env *env, char **cmd)
{
	char	**new;
	char	**clean_cmd;

	if (!cmd[1])
		return ;
	clean_cmd = ft_clean_cmd(env->envp, cmd + 1);
	new = ft_unset_envp(env->envp, clean_cmd);
	free(clean_cmd);
	if (!new)
		return ;
	free(env->envp);
	env->envp = new;
}
