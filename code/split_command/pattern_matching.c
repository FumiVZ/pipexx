/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_matching.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:39:48 by machrist          #+#    #+#             */
/*   Updated: 2024/05/21 16:07:43 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parthing.h"

static char	**insert_tab(char **str, char **add_str, size_t pos)
{
	size_t	i;
	size_t	j;
	char	**new_str;

	if (!add_str)
		return (NULL);
	new_str = malloc(sizeof(char *) * (ft_strstrlen(str) + ft_strstrlen(add_str)
				+ 1));
	if (!new_str)
		return (NULL);
	i = 0;
	j = 0;
	while (i < pos)
		new_str[i++] = str[j++];
	j = 0;
	while (add_str[j])
		new_str[i++] = add_str[j++];
	free(add_str);
	j = pos + 1;
	while (str[j])
		new_str[i++] = str[j++];
	new_str[i] = NULL;
	free(str);
	return (new_str);
}

static char	**add_str_env(char **str, t_env *env, size_t i, size_t pos)
{
	char	*tmp;
	char	**new_str;

	tmp = get_value(str[i] + pos, env->envp, env);
	free(str[i]);
	if (!tmp)
	{
		free_split(str, ft_strstrlen(str));
		return (NULL);
	}
	if (!*tmp)
		str[i] = tmp;
	else
	{
		new_str = insert_tab(str, ft_word_spliting(tmp, ifs_value(env->envp)),
				i);
		free(tmp);
		if (!new_str)
		{
			free_split(str, ft_strstrlen(str));
			return (NULL);
		}
		str = new_str;
	}
	return (str);
}

static char	**modified_str(char **str, char **envp, t_env *env, size_t i)
{
	size_t	pos;
	int		check;
	char	*tmp;
	char	**new_str;

	check = check_env_var(str[i]);
	pos = pos_var(str[i]);
	if (check == 1)
	{
		tmp = add_var_env(str[i], get_value(str[i] + pos, envp, env),
				get_len_name(str[i] + pos) + 1, pos);
		if (!tmp)
			return (NULL);
		free(str[i]);
		str[i] = tmp;
	}
	else if (check == 2)
	{
		new_str = add_str_env(str, env, i, pos);
		if (!new_str)
			return (NULL);
		str = new_str;
	}
	return (str);
}

static char	**variable_env(char **str, char **envp, t_env *env)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		str = modified_str(str, envp, env, i);
		if (!str)
		{
			ft_putstr_fd(MALLOC, 2);
			return (NULL);
		}
		i++;
	}
	return (str);
}

char	**pattern_matching(char **str, char **envp, t_env *env)
{
	size_t	i;
	char	*tmp;

	str = variable_env(str, envp, env);
	i = 0;
	while (str[i])
	{
		tmp = check_pattern_word(str[i]);
		if (!tmp)
		{
			free_split(str, ft_strstrlen(str));
			msg_err(MALLOC);
			return (NULL);
		}
		if (ft_strncmp(tmp, str[i], ft_strlen(str[i]) + 1) && *tmp)
		{
			free(str[i]);
			str[i] = tmp;
		}
		if (!*tmp)
			free(tmp);
		i++;
	}
	return (str);
}
