/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <rbernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 11:08:45 by rbernand          #+#    #+#             */
/*   Updated: 2016/01/14 16:55:30 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "vm.h"

void				*alloc_memory(void)
{
	void			*ptr;

	ptr = (void *)malloc(MEM_SIZE);
	if (!ptr)
		PERROR("malloc: allocation failed.");
	ft_bzero(ptr, MEM_SIZE);
	return (ptr);
}
