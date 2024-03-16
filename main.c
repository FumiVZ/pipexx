/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:03:30 by machrist          #+#    #+#             */
/*   Updated: 2024/03/15 19:50:20 by machrist         ###   ########.fr       */
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

int	is_sep(char *s)
{
	if (ft_strncmp(s, "&&", 2) == 0)
		return (AND);
	if (ft_strncmp(s, "||", 2) == 0)
		return (OR);
	if (ft_strncmp(s, ">>", 2) == 0)
		return (APPEND);
	if (ft_strncmp(s, "<<", 2) == 0)
		return (HERE_DOC);
	if (ft_strncmp(s, ">", 1) == 0)
		return (OUT);
	if (ft_strncmp(s, "<", 1) == 0)
		return (IN);
	if (ft_strncmp(s, "|", 1) == 0)
		return (PIPE);
	return (END);
}

void	minishell(char *line, t_env *env)
{
	size_t	i;

	i = 0;
	env->cmds = ft_split(line, ' ');
	if (!(env->cmds))
		return ;
	while (env->cmds[i])
	{
		if (!ft_strncmp(env->cmds[0], "echo", 5))
			ft_echo(env->cmds + i);
		env->clean_cmds = create_cmd(env->cmds + i);
		i += ft_strstrlen(env->clean_cmds);
	}
	free_split(env->cmds, ft_strstrlen(env->cmds));
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
