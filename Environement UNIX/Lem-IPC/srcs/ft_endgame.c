/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_endgame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erobert <erobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/27 15:15:05 by erobert           #+#    #+#             */
/*   Updated: 2014/05/27 15:28:49 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"

int			ft_endgame(char *ptr)
{
	char	tmp;
	int		i;
	int		k;

	i = 0;
	while (ptr[i] == '.')
		i++;
	tmp = ptr[i++];
	k = 0;
	while (i < HEIGHT * WIDTH)
	{
		if (ptr[i] != tmp && ptr[i] != '.')
			return (-1);
		if (ptr[i] == tmp)
			k++;
		i++;
	}
	if (i == HEIGHT * WIDTH && !k)
		return (-1);
	return (ft_print_result(" team: ", &tmp, 0));
}
