/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getcolony.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erobert <erobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/21 12:06:28 by erobert           #+#    #+#             */
/*   Updated: 2014/03/12 17:09:46 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lemin.h"

static int	ft_getnumero(t_lst *lst, char *name)
{
	int		numero;

	while (lst)
	{
		if (!ft_strcmp(name, lst->room[0]))
			numero = lst->numero;
		lst = lst->next;
	}
	return (numero);
}

static int	ft_filltab(t_colony *colony, t_lst *lst)
{
	t_lst	*start;
	int		i;
	int		j;

	start = lst;
	i = 0;
	while (i < colony->nb_rooms)
	{
		j = 0;
		while (j < colony->nb_rooms)
			colony->nodes[i][j++] = 0;
		i++;
	}
	while (lst)
	{
		if (!lst->room[2])
		{
			i = ft_getnumero(start, lst->room[0]);
			j = ft_getnumero(start, lst->room[1]);
			colony->nodes[i][j] = 1;
			colony->nodes[j][i] = 1;
		}
		lst = lst->next;
	}
	return (1);
}

static void	ft_nb_rooms(t_colony *colony, t_lst *lst)
{
	colony->nb_rooms = 0;
	while (lst)
	{
		if (lst->room[2])
		{
			lst->numero = colony->nb_rooms;
			colony->nb_rooms++;
		}
		else
			lst->numero = 0;
		lst = lst->next;
	}
}

static int	ft_rooms(t_colony *colony, t_lst *lst)
{
	int		i;

	ft_nb_rooms(colony, lst);
	colony->nodes = malloc(sizeof(*colony->nodes) * colony->nb_rooms);
	if (!colony->nodes)
		return (0);
	i = 0;
	while (i < colony->nb_rooms)
	{
		colony->nodes[i] = malloc(sizeof(**colony->nodes) * colony->nb_rooms);
		if (!colony->nodes[i++])
			return (0);
	}
	return (ft_filltab(colony, lst));
}

t_lst		*ft_getcolony(t_colony *colony)
{
	t_lst	*lst;

	lst = NULL;
	ft_getline(0, &colony->stock);
	colony->nb_ants = ft_atoi(colony->stock);
	if (colony->nb_ants < 1)
		return (0);
	if (!ft_getrooms(colony, &lst))
		return (0);
	if (!ft_rooms(colony, lst))
		return (0);
	return (lst);
}
