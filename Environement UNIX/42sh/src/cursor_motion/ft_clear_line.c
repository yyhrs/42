/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaron <tcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/09 16:23:28 by tcaron            #+#    #+#             */
/*   Updated: 2014/02/09 16:23:28 by tcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termcap.h>
#include <termios.h>
#include <sys/ioctl.h>
#include "../header.h"
#include "../libft.h"

void	ft_clear_line(t_input *final)
{
	struct winsize	ws;
	int				nb_lines;
	int				line_no;

	if (ioctl(0, TIOCGWINSZ, &ws) == -1)
		ft_putstr_fd("ft_clear_line\n", 2);
	nb_lines = (final->cursor_max + ft_prompt_len(0)) / ws.ws_col;
	line_no = ft_get_line_num(0);
	tputs(tgetstr("rc", NULL), 1, ft_putchar_term);
	if (line_no + 1 == ws.ws_row)
		return ;
	while (nb_lines + line_no > 0)
	{
		ft_putstr(CURSOR_DOWN);
		tputs(tgoto(tgetstr("ch", NULL), 0, 0), 1, ft_putchar_term);
		tputs(tgetstr("ce", NULL), 1, ft_putchar_term);
		nb_lines--;
	}
	return ;
}
