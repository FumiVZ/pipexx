/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:03:30 by machrist          #+#    #+#             */
/*   Updated: 2024/03/17 18:21:49 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

void	minishell(char *line, t_env *env)
{
	size_t	i;
	t_redir	redir;

	env->cmds = ft_word_spliting(line);
	if (!env->cmds)
		return ;
	pattern_matching(env->cmds, env->envp);
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
	char				*str;

	sa.sa_handler = signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) == -1 || sigaction(SIGQUIT, &sa,
			NULL) == -1)
		printf("Error: signal\n");
	while (1)
	{
		str = ft_color();
		line = readline(str);
		free(str);
		add_history(line);
		minishell(line, env);
	}
}

int ft_putchar(int c)
{
    char ch = (char)c;
    write(1, &ch, 1);
    return c; // Retournez le caractère, ou -1 en cas d'erreur
}

void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		if (signal == SIGINT)
		{
			ft_putstr_fd("\nminishell $ ", 1);
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
