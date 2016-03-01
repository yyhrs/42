/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dijkstra.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erobert <erobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/11 16:24:48 by erobert           #+#    #+#             */
/*   Updated: 2014/03/12 19:02:25 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lemin.h"

static int	ft_min_dist(int *dist, int *sptset, int nb_rooms)
{
	int		min;
	int		min_index;
	int		i;

	min = INT_MAX;
	i = 0;
	while (i < nb_rooms)
	{
		if (sptset[i] == 0 && dist[i] <= min)
		{
			min = dist[i];
			min_index = i;
		}
		i++;
	}
	return (min_index);
}

static int	ft_first_step(int *previous, int src, int end)
{
	if (previous[end] != src)
		return (ft_first_step(previous, src , previous[end]));
	return (end);
}

static void	ft_check_dist(int **nodes, int nb_rooms, int **tab, int *index)
{
	int		b;

	index[0] = ft_min_dist(tab[0], tab[1], nb_rooms);
	tab[1][index[0]] = 1;
	index[1] = 0;
	while (index[1] < nb_rooms)
	{
		b = tab[0][index[1]] + nodes[index[0]][index[1]] < tab[0][index[1]];
		b = b && !tab[1][index[1]] && nodes[index[0]][index[1]];
		if (b && tab[0][index[0]] != INT_MAX)
		{
			tab[2][index[1]] = index[0];
			tab[0][index[1]] = tab[0][index[0]] + nodes[index[0]][index[1]];
		}
		index[1]++;
	}
}

static int	**ft_init_tab(int nb_rooms, int src)
{
	int		**tab;
	int		i;

	tab = malloc(sizeof(*tab) * 3);
	if (!tab)
		return (NULL);
	tab[0] = malloc(sizeof(*tab) * nb_rooms);
	if (!tab[0])
		return (0);
	tab[1] = malloc(sizeof(*tab) * nb_rooms);
	if (!tab[1])
		return (0);
	tab[2] = malloc(sizeof(*tab) * nb_rooms);
	if (!tab[2])
		return (0);
	i = 0;
	while (i < nb_rooms)
	{
		tab[0][i] = INT_MAX;
		tab[1][i] = 0;
		tab[2][i++] = -1;
	}
	tab[0][src] = 0;
	return (tab);
}

int			ft_dijkstra(int **nodes, int nb_rooms, int src, int end)
{
	int		**tab;
	int		index[2] = {0, 0};
	int		i;
	int		res;

	tab = ft_init_tab(nb_rooms, src);
	if (!tab)
		return (-1);
	i = 0;
	while (i < nb_rooms - 1)
	{
		ft_check_dist(nodes, nb_rooms, tab, index);
		i++;
	}
	res = -1;
	if (tab[0][end] != INT_MAX)
		res = ft_first_step(tab[2], src, end);
	free(tab[0]);
	free(tab[1]);
	free(tab[2]);
	free(tab);
	return (res);
}
