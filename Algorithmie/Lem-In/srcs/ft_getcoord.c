/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getcoord.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erobert <erobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/21 13:13:18 by erobert           #+#    #+#             */
/*   Updated: 2014/02/21 17:32:57 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lemin.h"

static char	*ft_getword(char *line)
{
	char	*result;
	int		len;
	int		i;

	len = 0;
	while (line[len] && line[len] != ' ' && line[len] != '-')
		len++;
	result = malloc(sizeof(*result) * (len + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (i < len)
	{
		result[i] = line[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

int			ft_getcoord(t_lst **lst, char *line, int mode)
{
	t_lst	*elem;

	elem = malloc(sizeof(*elem));
	if (!elem || !line)
		return (0);
	elem->mode = mode;
	elem->room[0] = ft_getword(line);
	while (*line != ' ' && *line != '-')
		line++;
	elem->room[1] = ft_getword(++line);
	elem->room[2] = NULL;
	if (!elem->room[0] || !elem->room[1])
		return (0);
	while (*line && *line != ' ')
		line++;
	if (*line)
	{
		elem->room[2] = ft_getword(++line);
		if (!elem->room[2])
			return (0);
	}
	elem->next = *lst;
	*lst = elem;
	return (1);
}
