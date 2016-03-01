/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move_colony.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erobert <erobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/11 14:07:37 by erobert           #+#    #+#             */
/*   Updated: 2014/03/12 18:22:48 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void	ft_print_move(t_lst **tab, int i, int j, int first)
{
	if (!first)
		ft_putstr_fd(" ", 1);
	ft_putstr_fd("L", 1);
	ft_putnbr_fd(i + 1, 1);
	ft_putstr_fd("-", 1);
	ft_putstr_fd(tab[j]->room[0], 1);
}

static int	ft_move_others(t_colony *c, int *ants, int *b, int i)
{
	int		room;

	if (ants[i] != c->end)
	{
		room = ft_dijkstra(c->nodes, c->nb_rooms, ants[i], c->end);
		if (!b[room] || room == c->end)
		{
			b[room] = 1;
			c->nodes[ants[i]][room]++;
			c->nodes[room][ants[i]]++;
			ants[i] = room;
		}
		else
			return (0);
	}
	return (1);
}

static int	ft_move_batch(t_colony *c, int *ants, t_lst **tab, int j)
{
	int		b[c->nb_rooms];
	int		room;
	int		i;

	i = 0;
	while (i < c->nb_rooms)
		b[i++] = 0;
	room = ft_dijkstra(c->nodes, c->nb_rooms, ants[j], c->end);
	if (room == -1)
		return (0);
	c->nodes[ants[j]][room]++;
	c->nodes[room][ants[j]]++;
	ants[j] = room;
	b[room] = 1;
	ft_print_move(tab, j, ants[j], 1);
	i = 1 + j;
	while (i < c->nb_ants)
	{
		if (ft_move_others(c, ants, b, i++))
			ft_print_move(tab, i, ants[i - 1], 0);
		else
			break ;
	}
	ft_putendl_fd("", 1);
	return (1);
}

int			ft_move_colony(t_colony *c, t_lst **tab)
{
	int		ants[c->nb_ants];
	int		i;

	i = 0;
	while (i < c->nb_ants)
		ants[i++] = c->start;
	i = 0;
	while (ants[c->nb_ants - 1] != c->end)
	{
		if (!ft_move_batch(c, ants, tab, i))
			return (0);
		while (ants[i] == c->end && i < c->nb_ants)
			i++;
	}
	return (1);
}
