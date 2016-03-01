/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_playgame.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erobert <erobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/27 15:34:20 by erobert           #+#    #+#             */
/*   Updated: 2014/05/29 15:51:19 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include "lemipc.h"

static char		ft_checkslot(t_data *d, int slot)
{
	if (slot < 0 || slot >= (int)d->size)
		return ('\0');
	if (d->map[slot] != '.' && d->map[slot] != d->map[d->slot])
		return (d->map[slot]);
	return ('\0');
}

static void		ft_checkclose(t_data *d, char *tab)
{
	char		tmp;

	if ((tmp = ft_checkslot(d, d->slot - 1)))
		tab[tmp - '0']++;
	if ((tmp = ft_checkslot(d, d->slot + 1)))
		tab[tmp - '0']++;
	if ((tmp = ft_checkslot(d, d->slot + WIDTH - 1)))
		tab[tmp - '0']++;
	if ((tmp = ft_checkslot(d, d->slot + WIDTH)))
		tab[tmp - '0']++;
	if ((tmp = ft_checkslot(d, d->slot + WIDTH + 1)))
		tab[tmp - '0']++;
	if ((tmp = ft_checkslot(d, d->slot - WIDTH - 1)))
		tab[tmp - '0']++;
	if ((tmp = ft_checkslot(d, d->slot - WIDTH)))
		tab[tmp - '0']++;
	if ((tmp = ft_checkslot(d, d->slot - WIDTH + 1)))
		tab[tmp - '0']++;
}

static int		ft_deadplayer(t_data *d)
{
	char		tab[9];
	int			i;

	i = 0;
	while (i < 9)
		tab[i++] = 0;
	ft_checkclose(d, tab);
	i = 0;
	while (i < 9)
	{
		if (tab[i++] > 1)
			return (-1);
	}
	return (0);
}

static void		ft_moveplayer(t_data *d)
{
	int			tmp;

	if ((d->map[d->slot] - '0') % 2)
		tmp = (d->slot + 1) % d->size;
	else
		tmp = (d->slot > 0 ? d->slot - 1 : d->size - 1);
	if (d->map[tmp] != '.')
		return ;
	d->map[tmp] = d->map[d->slot];
	d->map[d->slot] = '.';
	d->slot = tmp;
}

int				ft_playgame(t_data *d)
{
	struct sembuf op[1];

	op[0].sem_num = 1;
	op[0].sem_op = -1;
	op[0].sem_flg = SEM_UNDO;
	semop(d->semid, op, 1);
	op[0].sem_op = 1;
	if (ft_deadplayer(d))
	{
		d->map[d->slot] = '.';
		semop(d->semid, op, 1);
		ft_print_result(" you are dead", "", -1);
		return (0);
	}
	ft_moveplayer(d);
	semop(d->semid, op, 1);
	return (1);
}
