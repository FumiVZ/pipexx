/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 13:30:59 by machrist          #+#    #+#             */
/*   Updated: 2024/05/21 16:00:56 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <signal.h>

static void	minishell(t_env *env, char *line)
{
/* 	if (!check_syntax(line))
	{
		ft_putstr_fd("minishell: syntax error\n", 2);
		return ;
	} */
	env->cmds = ft_word_spliting(line, " \t");
	if (!(env->cmds))
		return ;
	init_pipex(env);
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
