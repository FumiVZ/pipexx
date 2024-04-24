/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ascii_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:28:09 by machrist          #+#    #+#             */
/*   Updated: 2024/04/24 18:06:10 by machrist         ###   ########.fr       */
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

char    *sort_result(char *result)
{
    char    **tab;
    char    *tmp;
    size_t  i;

    if (!result)
        return (msg_err_ptr(MALLOC));
    tab = ft_split(result, ' ');
    free(result);
    if (!tab)
        return (msg_err_ptr(MALLOC));
    ascii_sort(tab);
    result = ft_strjoin(tab[0], " ");
    if (!result)
    {
        free_split(tab, ft_strstrlen(tab));
        return (msg_err_ptr(MALLOC));
    }
    free(tab[0]);
    tab[0] = NULL;
    i = 1;
    while (tab[i])
    {
        tmp = ft_strjoin(result, tab[i]);
        if (!tmp)
        {
            free(result);
            free(tab[i]);
            return (msg_err_ptr(MALLOC));
        }
        free(result);
        free(tab[i]);
        if (tab[i + 1])
            result = ft_strjoin(tmp, " ");
        else
            result = ft_strdup(tmp);
        if (!result)
        {
            free(tmp);
            return (msg_err_ptr(MALLOC));
        }
        free(tmp);
        tab[i] = NULL;
        i++;
    }
    free(tab);
    return (result);
}

