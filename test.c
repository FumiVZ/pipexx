#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

int	main(void)
{
	int	red;
	int	green;
	int	blue;
	int	bg_red;
	int	bg_green;
	int	bg_blue;

	for (int seed = 0; seed != 200000; seed++)
	{
		red = ft_rand(0, 255);
		green = ft_rand(0, 255);
		blue = ft_rand(0, 255);
		bg_red = ft_rand(0, 255);
		bg_green = ft_rand(0, 255);
		bg_blue = ft_rand(0, 255);
		usleep(1000 * 200);
		printf("\033[%d;38;2;%d;%d;%d;48;2;%d;%d;%dmTexte avec couleur,\
effet et fond aléatoires\n",5 , red, green, blue,
			bg_red, bg_green, bg_blue);
	}
	return (0);
}
