/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 13:30:59 by machrist          #+#    #+#             */
/*   Updated: 2024/05/04 06:43:03 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <signal.h>

static bool	ft_builtins(t_env *env, char **args)
{
	if (!ft_strncmp(args[0], "echo", 5))
		ft_echo(env, args);
	else if (!ft_strncmp(args[0], "exit", 5))
		ft_exit(env);
	else if (!ft_strncmp(args[0], "cd", 3))
		ft_cd(env, args);
	else if (!ft_strncmp(args[0], "env", 4))
		ft_env(env);
	else if (!ft_strncmp(args[0], "pwd", 4))
		ft_pwd(env);
	else if (!ft_strncmp(args[0], "export", 7))
		ft_export(env, args);
	else if (!ft_strncmp(args[0], "unset", 6))
		ft_unset(env, args);
	else
		return (0);
	return (1);
}

static void	minishell(t_env *env, char *line)
{
	size_t	i;
	t_redir	redir;

	if (!check_syntax(line))
		return ;
	env->cmds = ft_word_spliting(line, " \t");
	if (!env->cmds)
		return ;
	env->cmds = pattern_matching(env->cmds, env->envp, env);
	if (!(env->cmds))
		return ;
	i = 0;
	while (env->cmds[i])
	{
		env->clean_cmds = create_cmd(env->cmds + i);
		if (!ft_builtins(env, env->clean_cmds))
			env->status = exec_cmd(env, &redir);
		i += ft_strstrlen(env->clean_cmds);
		free_split(env->clean_cmds, ft_strstrlen(env->clean_cmds));
	}
	free_split(env->cmds, ft_strstrlen(env->cmds));
}

static void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ft_readline(t_env *env)
{
	char	*line;

	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			ft_exit_error(env, 0);
		if (*line)
		{
			add_history(line);
			minishell(env, line);
		}
	}
}

int	main(int ac, char **av, char **envp)
{
	t_env				env;
	struct sigaction	sa;

	(void)ac;
	(void)av;
	sa.sa_handler = &signal_handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGINT, &sa, NULL) == -1)
		printf("Error: signal\n");
	signal(SIGQUIT, SIG_IGN);
	env.status = 0;
	env.envp = ft_init_env(envp);
	ft_readline(&env);
	return (0);
}
