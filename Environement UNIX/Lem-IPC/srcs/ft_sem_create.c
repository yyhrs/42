/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sem_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erobert <erobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/28 17:19:14 by erobert           #+#    #+#             */
/*   Updated: 2014/05/28 18:07:10 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include "lemipc.h"

int					ft_sem_create(t_data *d)
{
	key_t			key;
	unsigned short	values[1];

	key = 42;
	d->semid = semget(key, 1, IPC_CREAT);
	if (d->semid == -1)
		return (ft_print_result(" semget: create", "", -1));
	values[0] = 1;
	d->sem.array = values;
	if (semctl(d->semid, 0, IPC_SET, d->sem) == -1)
		return (ft_print_result(" semctl: set", "", -1));
	return (0);
}
