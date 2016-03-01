/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cursor_motion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaron <tcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/09 16:23:35 by tcaron            #+#    #+#             */
/*   Updated: 2014/02/09 16:23:35 by tcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <termcap.h>
#include <termios.h>
#include <sys/ioctl.h>
#include "../header.h"
#include "../libft.h"

static void		ft_rigth_motion(t_input *final, int col)
{
	int				pos;
	int				no_lignes;

	if (final->cursor_pos == final->cursor_max)
		return ;
	pos = final->cursor_pos + ft_prompt_len(0);
	no_lignes = (pos / col);
	pos = final->cursor_pos + ft_prompt_len(0) - (no_lignes * col);
	tputs(tgoto(tgetstr("cm", NULL), pos, no_lignes + ft_get_line_num(0)),
			1, ft_putchar_term);
	final->cursor_pos += 1;
	return ;
}

static void		ft_left_motion(t_input *final, int col)
{
	int				pos;
	int				no_lignes;
	static int		check = 0;

	if (final->cursor_pos == 1)
		return ;
	pos = final->cursor_pos + ft_prompt_len(0);
	no_lignes = (pos / col);
	pos -= (no_lignes * col);
	if (pos == 1 && !check)
	{
		pos = col + 1;
		no_lignes--;
		check++;
	}
	else if (check == 1)
	{
		pos = col;
		no_lignes--;
		check = 0;
	}
	tputs(tgoto(tgetstr("cm", NULL), pos - 2, no_lignes + ft_get_line_num(0)),
			1, ft_putchar_term);
	final->cursor_pos -= 1;
	return ;
}

char			*ft_check_key_LR(t_input *final, int value)
{
	struct winsize	ws;

	if (ioctl(0, TIOCGWINSZ, &ws) == -1)
		ft_putstr_fd("ft_check_key_LR\n", 2);
	if (value == 1)
		ft_rigth_motion(final, ws.ws_col);
	else if (value == -1)
		ft_left_motion(final, ws.ws_col);
	return (final->result);
}
