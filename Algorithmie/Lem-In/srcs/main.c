/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erobert <erobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/21 11:37:16 by erobert           #+#    #+#             */
/*   Updated: 2014/03/12 19:03:33 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lemin.h"

static int		ft_launch(t_colony *c, t_lst *lst)
{
	t_lst		*tab[c->nb_rooms];

	while (lst)
	{
		if (lst->mode == 1)
			c->start = lst->numero;
		if (lst->mode == 2)
			c->end = lst->numero;
		if (lst->room[2])
			tab[lst->numero] = lst;
		lst = lst->next;
	}
	if (ft_dijkstra(c->nodes, c->nb_rooms, c->start, c->end) == -1)
		return (0);
	ft_putendl_fd(c->stock, 1);
	ft_putstr_fd("\n", 2);
	return (ft_move_colony(c, tab));
}

int				main(void)
{
	t_colony	colony;
	t_lst		*lst;

	lst = ft_getcolony(&colony);
	if (!lst)
		ft_putstr_fd("ERROR\n", 2);
	else if (!ft_launch(&colony, lst))
		ft_putstr_fd("ERROR\n", 2);
	free(colony.stock);
	return (0);
}
