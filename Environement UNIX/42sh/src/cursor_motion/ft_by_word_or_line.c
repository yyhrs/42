/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_by_word_or_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaron <tcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/09 16:23:17 by tcaron            #+#    #+#             */
/*   Updated: 2014/02/09 16:23:18 by tcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termcap.h>
#include <termios.h>
#include <sys/ioctl.h>
#include "../header.h"
#include "../libft.h"

void			ft_prev_word(t_input *final)
{
	if (final->cursor_pos == 1)
		return ;
	final->cursor_pos--;
	while (final->cursor_pos > 1
			&& final->result[final->cursor_pos - 2] != ' ')
		final->cursor_pos--;
}

void			ft_next_word(t_input *final)
{
	if (final->cursor_pos == final->cursor_max)
		return ;
	final->cursor_pos++;
	while (final->cursor_pos < final->cursor_max
			&& final->result[final->cursor_pos - 2] != ' ')
		final->cursor_pos++;
}

void			ft_next_line(t_input *final)
{
	struct winsize	ws;
	int				no_next_line;

	if (ioctl(0, TIOCGWINSZ, &ws) == -1)
		ft_putstr_fd("ft_next_line\n", 2);
	if (final->cursor_pos <= final->cursor_max - ws.ws_col)
		final->cursor_pos--;
	no_next_line = (final->cursor_pos + ft_prompt_len(0)) + ws.ws_col;
	if (no_next_line > (final->cursor_max + ft_prompt_len(0)))
		final->cursor_pos = final->cursor_max;
	else
		final->cursor_pos = no_next_line - ft_prompt_len(0);
	return ;
}

void			ft_prev_line(t_input *final)
{
	struct winsize	ws;
	int				no_prev_line;

	if (ioctl(0, TIOCGWINSZ, &ws) == -1)
		ft_putstr_fd("ft_prev_line\n", 2);
	if (((final->cursor_pos + ft_prompt_len(0)) / ws.ws_col)
		!= (final->cursor_max + ft_prompt_len(0)) / ws.ws_col)
		final->cursor_pos--;
	no_prev_line = (final->cursor_pos + ft_prompt_len(0)) - ws.ws_col;
	if (no_prev_line < 0 || no_prev_line <= ft_prompt_len(0))
		final->cursor_pos = 1;
	else
		final->cursor_pos = no_prev_line - ft_prompt_len(0);
	return ;
}
