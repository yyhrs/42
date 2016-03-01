/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erobert <erobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/11 14:57:51 by erobert           #+#    #+#             */
/*   Updated: 2014/05/11 17:25:46 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "philo.h"

static int	ft_tex_color(t_img *t, int i, int j)
{
	t_color	c;
	int		bpp;
	int		k;

	bpp = t->bpp / 8;
	k = j * bpp * t->size[0] + i % t->size[0] * bpp;
	c.rgba[0] = t->data[k++];
	c.rgba[1] = t->data[k++];
	c.rgba[2] = t->data[k];
	c.rgba[3] = 0;
	return (c.c);
}

static void	ft_draw_philosopher(t_data *d, int id, t_img *t)
{
	int		i;
	int		j;
	int		index[2];

	index[0] = 20;
	i = id * 100 + 24;
	while (++i < id * 100 + 75)
	{
		index[1] = 0;
		j = 49;
		while (++j < 125)
		{
			ft_put_pixel_to_image(d, i, j, ft_tex_color(t, index[0], index[1]));
			index[1]++;
		}
		index[0]++;
	}
}

static int	ft_img_init(t_data *d, t_img *i)
{
	i->ptr = mlx_new_image(d->mlx_ptr, 700, 200);
	if (i->ptr)
		i->data = mlx_get_data_addr(i->ptr, &i->bpp, &i->line, &i->endian);
	else
		return (-1);
	return (0);
}

static int	ft_tex_init(t_data *d, t_img *t, int i)
{
	char	*file;

	if (!i)
		file = "philosophers/aristotle.xpm";
	else if (i == 1)
		file = "philosophers/cicero.xpm";
	else if (i == 2)
		file = "philosophers/epicurus.xpm";
	else if (i == 3)
		file = "philosophers/plato.xpm";
	else if (i == 4)
		file = "philosophers/pythagoras.xpm";
	else if (i == 5)
		file = "philosophers/seneca.xpm";
	else
		file = "philosophers/socrates.xpm";
	t->ptr = mlx_xpm_file_to_image(d->mlx_ptr, file, &t->size[0], &t->size[1]);
	if (t->ptr)
		t->data = mlx_get_data_addr(t->ptr, &t->bpp, &t->line, &t->endian);
	else
		return (-1);
	return (0);
}

int			ft_mlx_init(t_data *d)
{
	t_img		t;
	int			i;

	if ((d->mlx_ptr = mlx_init()) == 0)
		return (-1);
	d->mlx_win = mlx_new_window(d->mlx_ptr, 700, 200, "PHILO");
	if (!d->mlx_win)
		return (-1);
	if (ft_img_init(d, &d->img))
		return (-1);
	i = -1;
	while (++i < 7)
	{
		if (ft_tex_init(d, &t, i))
			return (-1);
		ft_draw_philosopher(d, i, &t);
		mlx_destroy_image(d->mlx_ptr, t.ptr);
	}
	return (0);
}
