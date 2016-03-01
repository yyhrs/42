/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_drop_sticks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdezier <hdezier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/11 19:01:25 by hdezier           #+#    #+#             */
/*   Updated: 2014/05/11 19:01:26 by hdezier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_drop_stick(int id, int *sticks, pthread_mutex_t *lock)
{
	if (sticks[id] == id)
	{
		pthread_mutex_lock(&lock[id]);
		sticks[id] = -1;
		pthread_mutex_unlock(&lock[id]);
	}
	if (sticks[(id + 1) % 7] == id)
	{
		pthread_mutex_lock(&lock[(id + 1) % 7]);
		sticks[(id + 1) % 7] = -1;
		pthread_mutex_unlock(&lock[(id + 1) % 7]);
	}
}

void	ft_drop_hp(int *sticks, t_philosopher *p, int id)
{
	int	i;
	int	busy_time;
	int	current_state;

	i = -1;
	current_state = p[id].state;
	busy_time = p[id].state == 0 ? REST_T : THINK_T;
	while (++i < busy_time)
	{
		if (current_state == 1
			&& sticks[id] != id && sticks[(id + 1) % 7] != id)
		{
			current_state = 0;
			p[id].state = 0;
			busy_time = REST_T;
			i = 0;
		}
		usleep(SEC);
		p[id].hp--;
	}
}
