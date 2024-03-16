/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:47:33 by machrist          #+#    #+#             */
/*   Updated: 2024/03/16 14:59:41 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_unset_envp(t_env *env, char *var)
{
	t_envp	*tmp;
	t_envp	*prev;

	tmp = env->envp;
	prev = NULL;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, var, ft_strlen(var) + 1))
		{
			if (prev)
				prev->next = tmp->next;
			else
				env->envp = tmp->next;
			free(tmp->name);
			free(tmp->value);
			free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}

}

void	ft_unset_set(t_env *env, char *var)
{
	t_set	*tmp;
	t_set	*prev;

	tmp = env->set;
	prev = NULL;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, var, ft_strlen(var) + 1))
		{
			if (prev)
				prev->next = tmp->next;
			else
				env->set = tmp->next;
			free(tmp->name);
			free(tmp->value);
			free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

void	ft_unset(t_env *env, char **cmd)
{
	size_t	i;

	if (!cmd[1])
		return ;
	i = 1;
	while (cmd[i])
	{
		ft_unset_envp(env, cmd[i]);
		ft_unset_set(env, cmd[i]);
		++i;
	}
}
