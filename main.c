/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:03:30 by machrist          #+#    #+#             */
/*   Updated: 2024/02/29 15:08:46 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>


void	ft_init_env(t_env *env, char **envp)
{
	size_t	i;

	if (!envp)
	{
		env->envp = malloc(1);
		if (!env->envp)
			exit(1);
		env->envp[0] = NULL;
		env->history = NULL;
		return ;
	}
	env->history = NULL;
	env->envp = malloc(ft_strstrlen(envp) + 1);
	if (!env->envp)
		exit(1);
	i = 0;
	while (envp[i])
	{
		env->envp[i] = malloc(ft_strlen(envp[i]) + 1);
		if (!env->envp[i])
		{
			while (i)
				free(env->envp[i--]);
			free(env->envp);
			exit(1);
		}
		ft_strlcpy(env->envp[i], envp[i], ft_strlen(envp[i]) + 1);
		i++;
	}
}

/*
void	check_builtins(t_env *env)
{
	int	i;

	while (env->history->cmd_all[i])
	{
		if (ft_strncmp(env->history->cmd_all[i], "exit", 5) == 0)
			ft_exit(env->history, NULL);
		else if (ft_strncmp(env->envp[0], "history", 7) == 0)
			ft_history(env->history);
		else if (ft_strncmp(env->envp[0], "cd", 3) == 0)
			ft_cd(env->history->cmd_all[i]);
		else if (ft_strncmp(env->envp[0], "pwd", 4) == 0)
			ft_pwd();
		else if (ft_strncmp(env->envp[0], "export", 7) == 0)
			ft_export(env->history->cmd_all[i]);
		else if (ft_strncmp(env->envp[0], "unset", 6) == 0)
			ft_unset(env->history->cmd_all[i]);
		else if (ft_strncmp(env->envp[0], "env", 4) == 0)
			ft_env(env->envp);
		else if (ft_strncmp(env->envp[0], "echo", 5) == 0)
			ft_echo(env->history->cmd_all[i]);
		else
			ft_putstr_fd("minishell: command not found: ", 1);
		i++;
	}
}*/

void	minishell(char *line, t_env *env)
{
	ft_init_history(env, line);
	if (!ft_strncmp(find_last_history(env)->cmd_all[0], "exit", 4))
	{
		ft_exit(env->history);
	}
	else if (!ft_strncmp(find_last_history(env)->cmd_all[0], "history", 8))
	{
		ft_history(env->history);
	}
	else if (!ft_strncmp(find_last_history(env)->cmd_all[0], "env", 3))
	{
		ft_env(env);
	}
	else if (!ft_strncmp(find_last_history(env)->cmd_all[0], "echo", 4))
	{
		ft_echo(find_last_history(env)->cmd_all);
	}
	else if (!ft_strncmp(find_last_history(env)->cmd_all[0], "pwd", 3))
	{
		ft_pwd();
	}
	else if (!ft_strncmp(find_last_history(env)->cmd_all[0], "cd", 2))
	{
		ft_cd(find_last_history(env)->cmd_all, env);
	}
	else
	{
		ft_putstr_fd("minishell: command not found: ", 1);
		ft_putendl_fd(line, 1);
	}
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_env	env;

	(void)ac;
	(void)av;
	ft_init_env(&env, envp);
	while (1)
	{
		printf("%s minishell$ ", getcwd(NULL, 0));
		line = readline(NULL);
		if (!line)
			return (ft_exit_error(env.history, NULL), 1);
		add_history(line);
		minishell(line, &env);
	}
	return (0);
}
