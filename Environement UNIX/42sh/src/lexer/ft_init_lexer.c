/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_lexer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaron <tcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/09 16:24:51 by tcaron            #+#    #+#             */
/*   Updated: 2014/02/09 16:24:51 by tcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"
#include "../libft.h"
#include <stdlib.h>

t_seq	*ft_init_seq(void)
{
	t_seq	*seq;

	seq = (t_seq *)ft_malloc(sizeof(t_seq));
	seq->cmd = NULL;
	seq->path = NULL;
	seq->func = NULL;
	seq->args = ft_strnew(1);
	seq->extra = NULL;
	seq->exec_tab = NULL;
	seq->next = NULL;
	seq->prev = NULL;
	seq->file = 0;
	return (seq);
}
