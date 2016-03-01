/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erobert <erobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/26 16:27:01 by erobert           #+#    #+#             */
/*   Updated: 2014/05/29 15:54:14 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <time.h>
#include <stdlib.h>
#include <sys/shm.h>
#include "lemipc.h"

static int			ft_usage(char *str)
{
	ft_putstr_fd("usage: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(" [0-9]", 2);
	return (-1);
}

static int			ft_find_slot(t_data *d)
{
	size_t			i;

	srand(time(NULL));
	d->slot = rand() % d->size;
	i = d->size;
	while (d->map[d->slot] != '.' && i > 0)
	{
		d->slot = rand() % d->size;
		i--;
	}
	if (!i)
	{
		if (d->master && shmdt(d->map))
			return (ft_print_result(" shmdt", "", -1));
		if (d->master && shmctl(d->shmid, IPC_RMID, 0))
			return (ft_print_result(" shmctl", "", -1));
		return (ft_print_result(" can't find a proper slot", "", -1));
	}
	return (0);
}

static void			ft_print_map(char *map, int master)
{
	size_t			i;

	if (!ALL && !master)
		return ;
	ft_putstr_fd("\033[H", 1);
	ft_putstr_fd("\033[2J", 1);
	i = 0;
	while (i < HEIGHT * WIDTH)
	{
		write(1, map + i, WIDTH);
		write(1, "\n", 1);
		i += WIDTH;
	}
	usleep(SLEEP_T);
}

static void			ft_close(t_data *d)
{
	unlink("tmp");
	if (d->master && shmdt(d->map))
		ft_print_result(" shmdt", "", -1);
	if (d->master && shmctl(d->shmid, IPC_RMID, 0))
		ft_print_result(" shmctl", "", -1);
}

int					main(int ac, char **av)
{
	static t_data	d = {NULL, HEIGHT * WIDTH, 0, 0, 0, 0, {0}};
	int				i;

	if (ac != 2 || av[1][1] || av[1][0] < '0' || av[1][0] > '9')
		return (ft_usage(av[0]));
	if (ft_shm_create(&d))
		return (-1);
	if (open("tmp", O_RDONLY) == -1)
	{
		d.master = 1;
		close(open("tmp", O_CREAT, 0666));
		i = -1;
		while (++i < d.size)
			d.map[i] = '.';
	}
	if (ft_find_slot(&d))
		return (-1);
	d.map[d.slot] = av[1][0];
	while (ft_endgame(d.map) && ft_playgame(&d))
		ft_print_map(d.map, d.master);
	if (d.master)
		ft_close(&d);
	return (0);
}
