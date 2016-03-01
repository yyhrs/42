/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <rbernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 15:23:52 by rbernand          #+#    #+#             */
/*   Updated: 2016/01/11 20:15:17 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>
#include <unistd.h>

static int		swap_endian(int value)
{
	int				out;

	out = value << 24;
	out |= ((value << 8) & 0x00ff0000);
	out |= ((value >> 8) & 0x0000ff00);
	out |= (value >> 24);
	return (out);
}

void			write_header(int fd, t_header *header)
{
	header->magic = swap_endian(header->magic);
	header->prog_size = swap_endian(header->prog_size);
	write(fd, header, sizeof(t_header));
}
