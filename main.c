/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:03:30 by machrist          #+#    #+#             */
/*   Updated: 2024/03/13 16:05:16 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>

void	ft_init_pwd(t_env *env)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_putstr_fd("minishell: ", 1);
		ft_putstr_fd(strerror(errno), 1);
		ft_putstr_fd("\n", 1);
	}
	else
	{
		env->envp = malloc(sizeof(t_envp *));
		if (!env->envp)
			exit(1);
		env->envp->name = malloc(4);
		if (!env->envp->name)
			exit(1);
		env->envp->name = "PWD";
		env->envp->value = pwd;
		env->envp->next = NULL;
	}
}

void	ft_add_envp(t_env *env, char *name, char *value)
{
	t_envp	*new;
	t_envp	*tmp;

	new = malloc(sizeof(t_envp));
	if (!new)
		exit(1);
	new->name = malloc(ft_strlen(name) + 1);
	ft_strlcpy(new->name, name, (size_t)(ft_strlen(name) + 1));
	new->value = malloc(ft_strlen(value) + 1);
	ft_strlcpy(new->value, value, (size_t)(ft_strlen(value) + 1));
	new->next = NULL;
	if (!env->envp)
	{
		env->envp = new;
		return ;
	}
	tmp = env->envp;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	ft_init_env(t_env *env, char **envp)
{
	size_t	i;
	size_t	j;

	if (!envp)
	{
		ft_init_pwd(env);
		return ;
	}
	env->envp = NULL;
	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] && envp[i][j] != '=')
			++j;
		envp[i][j] = '\0';
		ft_add_envp(env, envp[i], envp[i] + j + 1);
		i++;
	}
}
//il faut que tu modfies cette partie pour y a jouter l'exec de la command avec aussi les appel de fonction builtins normalement elles marchent toutes 
void	minishell(char *line, t_env *env)
{
	char	**cmd;

	cmd = ft_split(line, ' ');
	if (!ft_strncmp(cmd[0], "exit", 4))
	{
		ft_exit(env, cmd);
	}
	else if (!ft_strncmp(cmd[0], "env", 3))
	{
		ft_env(env);
	}
	else if (!ft_strncmp(cmd[0], "echo", 4))
	{
		ft_echo(cmd);
	}
	else if (!ft_strncmp(cmd[0], "pwd", 3))
	{
		ft_pwd();
	}
	else if (!ft_strncmp(cmd[0], "cd", 2))
	{
		ft_cd(cmd, env);
	}
	else if (!ft_strncmp(cmd[0], "export", 6))
	{
		ft_export(env, cmd);
	}
	else if (!ft_strncmp(cmd[0], "unset", 5))
	{
		ft_unset(env, cmd);
	}
	else
	{
		ft_putstr_fd("minishell: command not found: ", 1);
		ft_putendl_fd(line, 1);
	}
	free_split(cmd, ft_strstrlen(cmd));
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_env	env;
	char	*pwd;

	(void)ac;
	(void)av;
	env.set = NULL;
	ft_init_env(&env, envp);
	while (1)
	{
		pwd = getcwd(NULL, 0);
		printf("%s minishell$ ", pwd);
		free(pwd);
		line = readline(NULL);
		if (!line)
			return (ft_exit_error(&env), 1);
		add_history(line);
		minishell(line, &env);
	}
	return (0);
}
