/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 18:06:32 by machrist          #+#    #+#             */
/*   Updated: 2024/03/16 20:56:08 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
		exit(1);
	i = 0;
	while (envp[i])
	{
		new[i] = malloc(ft_strlen(envp[i]) + 1);
		if (!new[i])
			exit(1);
		ft_strlcpy(new[i], envp[i], (size_t)(ft_strlen(envp[i]) + 1));
		i++;
	}
	new[i] = NULL;
	return (new);
}
