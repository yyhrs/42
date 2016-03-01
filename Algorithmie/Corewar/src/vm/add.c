/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <rbernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 14:14:40 by rbernand          #+#    #+#             */
/*   Updated: 2016/02/09 11:30:40 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			add(t_process *self, void *memory, t_player *players, t_process **p)
{
	int		i;
	int		rindex[3];

	(void)memory;
	(void)players;
	(void)p;
	i = -1;
	while (++i < 3)
	{
		rindex[i] = self->params[i] - 1;
		if (rindex[i] < 0 || rindex[i] >= REG_NUMBER)
		{
			self->carry = 0;
			return (self->size_params);
		}
	}
	self->registers[rindex[2]] = self->registers[rindex[0]] +
		self->registers[rindex[1]];
	self->carry = EVAL_CARRY(self->registers[rindex[2]]);
	return (self->size_params);
}
