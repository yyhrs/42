/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaron <tcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/09 16:24:14 by tcaron            #+#    #+#             */
/*   Updated: 2014/02/18 17:44:11 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "../header.h"
#include "../libft.h"

void		ft_exec(t_seq *seq)
{
	while (seq && seq->next)
	{
		if (seq->extra && seq->extra[0] == '|')
		{
			ft_pipe(seq);
			while (seq->extra && seq->extra[0] == '|')
			{
				if (!seq || !seq->next)
					return ;
				seq = seq->next;
			}
		}
		else if (seq->cmd == NULL)
			ft_putstr_fd("cmd not found\n", 2);
		else
			ft_launch(1, seq);
		seq = seq->next;
	}
}
