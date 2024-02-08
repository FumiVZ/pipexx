/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 10:21:20 by vzuccare          #+#    #+#             */
/*   Updated: 2024/02/08 15:27:43 by vzuccare         ###   ########lyon.fr   */
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

char	*dup_until_space(char *str)
{
	size_t	i;
	char	*ret;

	i = 0;
	while (str[i] && str[i] != 32)
		i++;
	ret = malloc(sizeof(char) * (i + 1));
	if (!ret)
		return (NULL);
	i = -1;
	while (str[++i] && str[i] != 32)
		ret[i] = str[i];
	ret[i] = '\0';
	return (ret);
}

char	*get_env_path(char **env)
{
	size_t	i;
	char	*default_path;

	default_path = "/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin";
	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
			return (env[i] + 5);
	}
	return (default_path);
}

char	**get_cmd(char **av, int ac)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	**tab;

	j = 0;
	i = 2;
	k = 0;
	tab = malloc(sizeof(char *) * (ac - 3));
	while (av[i])
	{
		while (av[i][j] == 32 && av[i][j])
			j++;
		if (ft_isalpha(av[i][j]) && av[i][j])
		{
			tab[k] = dup_until_space(&av[i][j]);
			k++;
		}
		i++;
	}
	tab[k] = NULL;
	return (tab);
}

char	**get_cmd_path(char *path, char **cmd)
{
	ssize_t	i;
	size_t	j;
	size_t	k;
	char	**temp;
	char	**tab;
	char	*tmp;

	i = -1;
	j = -1;
	k = -1;
	tab = malloc(sizeof(char *) * (ft_tablen(cmd) + 1));
	temp = ft_split(path, ':');
	while (cmd[i])
	{
		while (temp[++k])
		{
			tmp = ft_strjoin(temp[k], "/");
			tmp = ft_strjoin(tmp, cmd[i]);
			if (access(tmp, F_OK) == 0)
				tab[++j] = ft_strdup(tmp);
			free(tmp);
		}
		k = -1;
		i++;
	}
	tab[j] = NULL;
	return (tab);
}
