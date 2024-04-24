/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ascii_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:28:09 by machrist          #+#    #+#             */
/*   Updated: 2024/04/24 22:29:00 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parthing.h>

static void	swap(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static void	ascii_sort(char **tab)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (tab[i])
	{
		j = i + 1;
		while (tab[j])
		{
			if (ft_strncmp(tab[i], tab[j], ft_strlen(tab[i])) > 0)
				swap(&tab[i], &tab[j]);
			j++;
		}
		i++;
	}
}

static char	*set_result(char *result, char **tab)
{
	size_t	i;
	char	*tmp;

	i = 1;
	result = ft_strjoin(tab[0], " ");
	if (!result)
		return (msg_err_ptr(MALLOC));
	while (tab[i])
	{
		tmp = ft_strjoin(result, tab[i]);
		free(result);
		if (!tmp)
			return (msg_err_ptr(MALLOC));
		if (tab[i + 1])
			result = ft_strjoin(tmp, " ");
		else
			result = ft_strdup(tmp);
		free(tmp);
		if (!result)
			return (msg_err_ptr(MALLOC));
		i++;
	}
	return (result);
}

char	*sort_result(char *result)
{
	char	**tab;

	if (!result)
	{
		result = ft_strdup("");
		if (!result)
			return (msg_err_ptr(MALLOC));
		return (result);
	}
	tab = ft_split(result, ' ');
	free(result);
	if (!tab)
		return (msg_err_ptr(MALLOC));
	ascii_sort(tab);
	result = set_result(result, tab);
	free_split(tab, ft_strstrlen(tab));
	return (result);
}
