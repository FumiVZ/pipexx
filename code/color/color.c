/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 17:38:37 by machrist          #+#    #+#             */
/*   Updated: 2024/03/17 18:23:02 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_rand(int min, int max)
{
	int				fd;
	unsigned int	rand_val;

	fd = open("/dev/urandom", O_RDONLY);
	if (fd == -1)
	{
		perror("Erreur lors de l'ouverture de /dev/urandom");
		exit(EXIT_FAILURE);
	}
	if (read(fd, &rand_val, sizeof(rand_val)) != sizeof(rand_val))
	{
		perror("Erreur lors de la lecture de /dev/urandom");
		close(fd);
		exit(EXIT_FAILURE);
	}
	close(fd);
	return (min + (min + rand_val % (max - min + 1)) % (max - min + 1));
}

char	*ft_color(void)
{
	char		*str;
	char		*tmp;
	char		*nb;
	int			i;

	if (0)
	{
		i = 8;
		str = ft_strdup("\033[5;38;2;");
		while (--i)
		{
			tmp = str;
			nb = ft_itoa(ft_rand(0, 255));
			str = ft_strjoin(str, nb);
			free(nb);
			free(tmp);
			tmp = str;
			if (i == 3)
				str = ft_strjoin(str, ";48;2;");
			else if (i == 1)
				str = ft_strjoin(str, "mminishell $ ");
			else
				str = ft_strjoin(str, ";");
			free(tmp);
		}
	}
	else
		return (ft_strdup("minishell $ "));
	return (str);
}
