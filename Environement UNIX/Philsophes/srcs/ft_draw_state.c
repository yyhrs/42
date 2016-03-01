/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_state.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erobert <erobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/11 15:09:03 by erobert           #+#    #+#             */
/*   Updated: 2014/05/11 18:08:47 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "philo.h"

void			ft_draw_state(t_philosopher *p)
{
	static char	t[3][9] = {"REST", "THINK", "EAT"};
	int			i;
	int			j;

	i = p->id * 100 + 24;
	while (++i < p->id * 100 + 75)
	{
		j = 139;
		while (++j < 150)
		{
			if (p->state == 1)
				ft_put_pixel_to_image(p->d, i, j, 0x0000FF);
			else if (p->state == 2)
				ft_put_pixel_to_image(p->d, i, j, 0xFFFF00);
			else
				ft_put_pixel_to_image(p->d, i, j, 0x00FF00);
		}
	}
	ft_putnbr_fd(p->id, 1);
	ft_putstr_fd("\t", 1);
	ft_putnbr_fd(p->hp, 1);
	ft_putstr_fd("\t", 1);
	ft_putendl_fd(t[p->state], 1);
	if (p->id == 6)
		ft_putstr_fd("______________________\n", 1);
}
