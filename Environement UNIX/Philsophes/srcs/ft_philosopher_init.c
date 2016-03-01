/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philosopher_init.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erobert <erobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/08 16:21:42 by erobert           #+#    #+#             */
/*   Updated: 2014/05/11 18:12:01 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_philosopher_init(t_philosopher *p, t_data *d)
{
	int	i;

	i = -1;
	while (++i < 7)
	{
		p[i].id = i;
		p[i].hp = MAX_LIFE;
		p[i].d = d;
		p[i].state = 0;
	}
}
