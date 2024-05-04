/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_matching.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:39:48 by machrist          #+#    #+#             */
/*   Updated: 2024/05/04 06:17:18 by machrist         ###   ########.fr       */
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
	free(str[pos]);
	j = pos + 1;
	while (str[j])
		new_str[i++] = str[j++];
	new_str[i] = NULL;
	free(str);
	return (new_str);
}

static char	**variable_env(char **str, char **envp, t_env *env)
{
	size_t	i;
	size_t	pos;
	int		check;
	char	*tmp;
	char	**new_str;

	i = 0;
	while (str[i])
	{
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
			tmp = get_value(str[i] + pos, envp, env);
			if (!tmp)
				return (free_split(str, ft_strstrlen(str)), NULL);
			if (!*tmp)
			{
				free(str[i]);
				str[i] = tmp;
			}
			else
			{
				new_str = insert_tab(str, ft_word_spliting(tmp,
							ifs_value(envp)), i);
				if (!new_str)
				{
					free(tmp);
					free_split(str, ft_strstrlen(str));
					return (NULL);
				}
				str = new_str;
				free(tmp);
			}
		}
		i++;
	}
	return (str);
}

char	**pattern_matching(char **str, char **envp, t_env *env)
{
	size_t	i;

	str = variable_env(str, envp, env);
	i = 0;
	while (str[i])
	{
		str[i] = check_pattern_word(str[i]);
		i++;
	}
	return (str);
}
