/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:03:30 by machrist          #+#    #+#             */
/*   Updated: 2024/03/13 16:35:33 by machrist         ###   ########.fr       */
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
//je vais t'envoyer la command comme split juste avec le bon parthing avec les parenthese et tout
//et tu devras juste l'executer avec execve
//pour le path tu vas en avoir un dans envp si on l'a pas enlever de l'env 
//sinon tu l'auras dans set qui sera par defaut
//tu auras juste a chercher dans le name tu as meme pas besoin d'enlever le = il est enlever par defaut 
//si tu te demandes pourquoi j'ai mis env et set fait juste les commandes dans bash et tu vas comprendre la difference
// tu as pas besoin de free la command c'est fait automatiquement dans le parent mais dans le child oui
// tu peux si c'est plus simple rajouter la cmd dans la struct env pour la free plus facilement dans tes childs
// pareil la ligne est gerer par l'history donc pas besoin de le free 
// j'ai pas verfier les malloc donc c'est pas proteger 
// tu as la fonction ft_free dans exit qui s'occupe de free tout ce que j'ai creer dans l'env
// tu peux changer le nom des fonction minishell
// essaies de mettre tout les fonctions que tu pas dans le header en static histoire d'eviter les probleme de compatibilite 
// la struct c'est juste une liste chaine donc juste tu te deplace dedans
// j'ai pas de fonction pour les utiliser proprement mais tu peux les faire toi meme
// pareil si tu veux reogarniser les fichier fait toi plaisir je t'avou que j'ai fait ca de maniere degu
// c'est un vieux wildcard dans le makefile aussi 
// je te laisse faire les tests pour voir si ca marche bien


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
