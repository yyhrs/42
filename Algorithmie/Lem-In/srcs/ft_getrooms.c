/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getrooms.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erobert <erobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/21 12:35:19 by erobert           #+#    #+#             */
/*   Updated: 2014/03/12 19:04:33 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lemin.h"

static void	ft_stock_lines(t_colony *colony, char *line)
{
	char	*tmp;

	tmp = colony->stock;
	if (*line)
		colony->stock = ft_strjoin(colony->stock, "\n");
	colony->stock = ft_strjoin(colony->stock, line);
	free(tmp);
}

static int	ft_freestr(char *s1, char *s2, int ret)
{
	free(s1);
	if (s2)
		free(s2);
	return (ret);
}

static int	ft_start_end(t_colony *colony, t_lst **lst, char **line)
{
	char	*tmp;

	if (!ft_strcmp(*line, "##start"))
	{
		tmp = *line;
		if (!ft_getline(0, line) || !ft_getcoord(lst, *line, 1))
			return (ft_freestr(*line, tmp, 0));
		ft_stock_lines(colony, *line);
		free(tmp);
	}
	else if (!ft_strcmp(*line, "##end"))
	{
		tmp = *line;
		if (!ft_getline(0, line) || !ft_getcoord(lst, *line, 2))
			return (ft_freestr(*line, tmp, 0));
		ft_stock_lines(colony, *line);
		free(tmp);
	}
	else
		return (1);
	return (2);
}

static int	ft_isgood_line(char *line)
{
	int		k;

	if (*line == 'L')
		return (0);
	if (*line == '#')
		return (1);
	k = 0;
	while (*line)
	{
		if (*line == '-' && *line + 1)
			return (1);
		else if (*line == ' ' && *line + 1)
		{
			if (++k == 2)
				return (1);
		}
		line++;
	}
	return (0);
}

int			ft_getrooms(t_colony *colony, t_lst **lst)
{
	char	*line;
	int		k;

	while (ft_getline(0, &line))
	{
		ft_stock_lines(colony, line);
		if (!ft_isgood_line(line))
			return (ft_freestr(line, 0, 1));
		k = ft_start_end(colony, lst, &line);
		if (!k)
			return (ft_freestr(line, 0, 0));
		else if (k == 2)
			;
		else if (*line != '#' && !ft_getcoord(lst, line, 0))
			return (ft_freestr(line, 0, 0));
		free(line);
	}
	return (1);
}
