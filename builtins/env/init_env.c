/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 18:06:32 by machrist          #+#    #+#             */
/*   Updated: 2024/05/27 17:08:26 by machrist         ###   ########.fr       */
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

static void	alloc_env(char **new, char **envp)
{
	int	i;

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
}

// char	**ft_add_env(char **envp, char *name, char *value)
// {
// 	char	**new;
// 	char	*tmp;
// 	size_t	i;
// 	size_t	len;

// 	new = malloc(sizeof(char *) * (ft_strstrlen(envp) + 2));
// 	if (!new)
// 	{
// 		perror("minishell: error malloc");
// 		free_split(envp, ft_strstrlen(envp));
// 		return (NULL);
// 	}
// 	tmp = malloc(ft_strlen(name) + ft_strlen(value) + 2);
// 	if (!tmp)
// 	{
// 		free(new);
// 		free_split(envp, ft_strstrlen(envp));
// 		perror("minishell: error malloc");
// 		return (NULL);
// 	}
// 	tmp = ft_strlcpy(tmp, name, ft_strlen(name) + 1);
// 	tmp[ft_strlen(name) + 1] = '=';
// 	tmp[ft_strlen(name) + 2] = '\0';
// 	tmp = ft_strlcat(tmp, value, ft_strlen(name) + ft_strlen(value) + 2);
// 	i = 0;
// 	j = 0;
// 	while (envp[i])
// 	{
// 		new[j] = envp[i];
// 		if (!ft_strncmp(envp[i], name, ft_strlen(name) - 1))
// 		{
// 			free(envp[i]);
// 			new[i] = ft_strlcpy(new[i], tmp, ft_strlen(tmp) + 1);
// 			j++;
// 		}
// 		i++;
// 		j++;
// 	}
// 	new[i] = NULL;
// 	free(envp);
// 	return (new);
// }

char	**ft_init_pwd(char **envp)
{
	char	*pwd;
	char	*tmp;
	char	**new;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_putstr_fd("minishell: ", 2);
		perror("getcwd");
		exit(1);
	}
	new = malloc(sizeof(char *) * (ft_strstrlen(envp) + 2));
	if (!new)
		exit(1);
	tmp = ft_strjoin("PWD=", pwd);
	if (!tmp)
		exit(1);
	new[ft_strstrlen(envp)] = tmp;
	if (!new[ft_strstrlen(envp)])
		exit(1);
	new[ft_strstrlen(envp) + 1] = NULL;
	free(pwd);
	return (new);
}

char	**ft_init_env(char **envp)
{
	char	**new;

	if (!envp || !*envp)
	{
		new = ft_init_pwd(envp);
		return (new);
	}
	new = malloc(sizeof(char *) * (ft_strstrlen(envp) + 1));
	if (!new)
	{
		perror("minishell: error malloc");
		exit(1);
	}
	alloc_env(new, envp);
	return (new);
}
