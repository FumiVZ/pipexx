/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:03:30 by machrist          #+#    #+#             */
/*   Updated: 2024/03/16 23:22:05 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <signal.h>

t_env	*g_env;

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

void	print_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
}

void	minishell(char *line, t_env *env)
{
	size_t	i;
	t_redir	redir;

	env->cmds = ft_word_spliting(line);
	if (!env->cmds)
		return ;
	pattern_matching(env->cmds);
	if (!(env->cmds))
		return ;
	i = 0;
	while (env->cmds[i])
	{
		env->clean_cmds = create_cmd(env->cmds + i);
		if (!ft_strncmp(env->cmds[0], "echo", 5))
			ft_echo(env->cmds + i);
		else if (!ft_strncmp(env->cmds[0], "exit", 5))
			ft_exit(env, env->cmds + i);
		else
			env->status = exec_cmd(env, &redir);
		i += ft_strstrlen(env->clean_cmds);
		free_split(env->clean_cmds, ft_strstrlen(env->clean_cmds));
	}
	free_split(env->cmds, ft_strstrlen(env->cmds));
}
void	signal_handler(int signal);

void	ft_readline(t_env *env)
{
	char				*line;
	struct sigaction	sa;
	char				*pwd;

	sa.sa_handler = signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) == -1 || sigaction(SIGQUIT, &sa,
			NULL) == -1)
		printf("Error: signal\n");
	while (1)
	{
		pwd = getcwd(NULL, 0);
		if (!pwd)
			ft_exit_error(env, 1);
		line = readline(ft_strjoin(pwd, "\033[41m\033[5mmi\033[7mni\033[4;32mshell$ \033[1;33m"));
		free(pwd);
		add_history(line);
		minishell(line, env);
	}
}

void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		if (signal == SIGINT)
		{
			printf("\nminishell$ ");
		}
		else
			ft_exit(g_env, NULL);
	}
	if (signal == SIGQUIT)
	{
		ft_putstr_fd("\b\b  \b\b", 1);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_env	env;

	(void)ac;
	(void)av;
	env.envp = ft_init_env(envp);
	g_env = &env;
	ft_readline(&env);
	return (0);
}
