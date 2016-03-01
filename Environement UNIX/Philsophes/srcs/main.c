/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erobert <erobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/05 10:31:50 by erobert           #+#    #+#             */
/*   Updated: 2014/05/11 22:33:00 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "philo.h"

static pthread_mutex_t	g_lock[8];
static t_philosopher	g_p[7] = {};
static int				g_sticks[8] = {-1, -1, -1, -1, -1, -1, -1, -1};

static void				ft_philo_act(int id)
{
	g_p[id].state = 0;
	if (g_sticks[id] == id && g_sticks[(id + 1) % 7] == id)
	{
		g_p[id].state = 2;
		usleep(EAT_T * SEC);
		g_p[id].hp = MAX_LIFE;
		ft_drop_stick(id, g_sticks, g_lock);
		g_p[id].state = 0;
	}
	else if (g_sticks[id] == id || g_sticks[(id + 1) % 7] == id)
		g_p[id].state = 1;
	ft_drop_hp(g_sticks, g_p, id);
	ft_drop_stick(id, g_sticks, g_lock);
}

static void				ft_philo_chop(int id)
{
	int					left;
	int					right;

	left = (id == 6 ? 0 : id);
	right = (id == 6 ? 6 : left + 1);
	pthread_mutex_lock(&g_lock[left]);
	if (g_sticks[left] < 0 || (g_p[id].state == 0
			&& g_p[(id + 1) % 7].state == 1
			&& g_sticks[(id + 1) % 7] == (id + 1) % 7
			&& g_p[(id + 1) % 7].hp >= g_p[id].hp))
		g_sticks[left] = id;
	pthread_mutex_unlock(&g_lock[left]);
	pthread_mutex_lock(&g_lock[right]);
	if (g_sticks[right] < 0 || (g_p[id].state == 0
			&& g_p[(id + 6) % 7].state == 1
			&& g_sticks[id] == (id + 6) % 7
			&& g_p[(id + 6) % 7].hp >= g_p[id].hp))
		g_sticks[right] = id;
	pthread_mutex_unlock(&g_lock[right]);
}

static void				*ft_philo_routine(void *ptr)
{
	int					id;

	id = *((int *)ptr);
	while (g_p[id].hp > 0)
	{
		ft_philo_chop(id);
		ft_philo_act(id);
		pthread_mutex_lock(&g_lock[7]);
		if (g_sticks[7] == 1138)
		{
			pthread_mutex_unlock(&g_lock[7]);
			return (NULL);
		}
		pthread_mutex_unlock(&g_lock[7]);
	}
	pthread_mutex_lock(&g_lock[7]);
	ft_putnbr_fd(id, 1);
	ft_putendl_fd("\tDEAD", 1);
	g_sticks[7] = 1138;
	pthread_mutex_unlock(&g_lock[7]);
	return (NULL);
}

static void				ft_close(pthread_t *t)
{
	int					i;
	char				tmp;

	pthread_mutex_lock(&g_lock[7]);
	g_sticks[7] = 1138;
	pthread_mutex_unlock(&g_lock[7]);
	ft_putendl_fd("Now, it is time... To DAAAAAAAANCE ! ! !", 1);
	while (read(0, &tmp, 1))
		break ;
	i = -1;
	while (++i < 7)
	{
		if (pthread_join(t[i], NULL))
			ft_putendl_fd("Error: pthread_join", 2);
		pthread_detach(t[i]);
	}
	i = -1;
	while (++i < 8)
	{
		if (pthread_mutex_destroy(&g_lock[i]))
			ft_putendl_fd("Error: pthread_mutex_destroy", 2);
	}
}

int						main(void)
{
	pthread_t			t[7];
	int					i;
	t_data				d;

	if (ft_mlx_init(&d))
		return (0);
	ft_philosopher_init(g_p, &d);
	i = -1;
	while (++i < 8)
	{
		if (pthread_mutex_init(&g_lock[i], NULL))
			ft_putendl_fd("Error: pthread_mutex_init", 2);
	}
	i = -1;
	while (++i < 7)
	{
		if (pthread_create(&t[i], NULL, ft_philo_routine, &g_p[i].id))
			ft_putendl_fd("Error: pthread_create", 2);
	}
	ft_check_state(g_p, g_sticks);
	ft_close(t);
	return (0);
}
