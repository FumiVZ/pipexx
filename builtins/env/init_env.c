/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincent <vincent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 18:06:32 by machrist          #+#    #+#             */
/*   Updated: 2024/05/01 16:13:03 by vincent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ft_getenv(char **envp, char *name)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(name);
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], name, len - 1))
		{
			if (envp[i][len] != '=')
				return (NULL);
			return (envp[i] + len + 1);
		}
		i++;
	}
	return (NULL);
}

static char	**ft_init_pwd(void)
{
	char	*pwd;
	char	**new;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_putstr_fd("minishell: ", 2);
		perror("getcwd");
		exit(1);
	}
	new = malloc(sizeof(char *) * 2);
	if (!new)
		exit(1);
	new[0] = ft_strjoin("PWD=", pwd);
	if (!new[0])
		exit(1);
	new[1] = NULL;
	free(pwd);
	return (new);
}

char	**ft_init_env(char **envp)
{
	size_t	i;
	char	**new;

	if (!envp)
	{
		new = ft_init_pwd();
		return (new);
	}
	new = malloc(sizeof(char *) * (ft_strstrlen(envp) + 1));
	if (!new)
	{
		perror("minishell: error malloc");
		exit(1);
	}
	i = 0;
	while (envp[i])
	{
		new[i] = malloc(ft_strlen(envp[i]) + 1);
		if (!new[i])
		{
			free_split(new, i);
			perror("minishell: error malloc");
			exit(1);
		}
		ft_strlcpy(new[i], envp[i], ft_strlen(envp[i]) + 1);
		i++;
	}
	new[i] = NULL;
	return (new);
}
