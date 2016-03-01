/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_state.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erobert <erobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/11 17:27:56 by erobert           #+#    #+#             */
/*   Updated: 2014/05/11 18:10:06 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "philo.h"

static void	ft_draw_stick(t_data *d, int id, int state)
{
	int		i;
	int		j;

	i = id * 100 - 1;
	while (++i < id * 100 + 10)
	{
		j = 49;
		while (++j < 125)
		{
			if (state != -1)
				ft_put_pixel_to_image(d, i, j, 0xFF0000);
			else
				ft_put_pixel_to_image(d, i, j, 0xFFFFFF);
		}
	}
	mlx_put_image_to_window(d->mlx_ptr, d->mlx_win, d->img.ptr, 0, 0);
}

void		ft_check_state(t_philosopher *p, int *sticks)
{
	int		i;
	int		j;

	i = -1;
	while (++i < TIMEOUT && sticks[7] != 1138)
	{
		j = -1;
		while (++j < 7)
			ft_draw_state(&p[j]);
		j = -1;
		while (++j < 7)
			ft_draw_stick(p->d, j, sticks[j]);
		usleep(SEC);
	}
}
