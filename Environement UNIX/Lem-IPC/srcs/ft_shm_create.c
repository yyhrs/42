/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shm_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erobert <erobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/27 11:30:01 by erobert           #+#    #+#             */
/*   Updated: 2014/05/28 17:32:54 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include "lemipc.h"

int			ft_shm_create(t_data *d)
{
	key_t	key;

	key = KEY;
	d->shmid = shmget(key, d->size, IPC_CREAT | 0666);
	if (d->shmid == -1)
		return (ft_print_result(" shmget: create", "", -1));
	d->map = shmat(d->shmid, NULL, 0);
	if (d->map == (char *)-1)
		return (ft_print_result(" shmat: maps", "", -1));
	return (ft_sem_create(d));
}
