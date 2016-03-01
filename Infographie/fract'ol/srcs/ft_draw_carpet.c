/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_carpet.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erobert <erobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/30 17:46:45 by erobert           #+#    #+#             */
/*   Updated: 2015/01/30 18:07:04 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int			ft_draw_carpet(t_data *d, int x, int y)
{
	x += d->fract.pos[0] * 100 - d->size / 2;
	y += d->fract.pos[1] * 100 - d->size / 2;
	x *= d->zoom;
	y *= d->zoom;
	if (x < 0)
		x *= -1;
	if (y < 0)
		y *= -1;
	while (x > 0 || y > 0)
	{
		if (x % 3 == 1 && y % 3 == 1)
			return (255);
		x /= 3.0;
		y /= 3.0;
	}
	return (0);
}
