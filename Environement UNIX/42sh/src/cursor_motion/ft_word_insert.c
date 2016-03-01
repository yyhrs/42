/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_word_insert.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaron <tcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/09 16:23:53 by tcaron            #+#    #+#             */
/*   Updated: 2014/02/09 16:23:53 by tcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <termcap.h>
#include <termios.h>
#include <sys/ioctl.h>
#include "../header.h"
#include "../libft.h"
#include <fcntl.h>

int				ft_get_line_num(int value)
{
	int			ret;
	static char	input[100];
	int			fd;

	if (value)
	{
		fd = open("/dev/tty", O_RDWR | O_CREAT);
		ft_putstr_fd("\033[6n\0\n", fd);
		ret = read(fd, input, 100);
		input[ret] = '\0';
		close(fd);
	}
	return (ft_atoi(&input[2]) - 1);
}

void			ft_place_cursor(t_input *final)
{
	int				pos;
	struct winsize	ws;
	int				no_lignes;
	static int		prev = 0;

	if (ioctl(0, TIOCGWINSZ, &ws) == -1)
		ft_putstr_fd("ft_place_cursor\n", 2);
	pos = final->cursor_pos + ft_prompt_len(0);
	no_lignes = (pos / ws.ws_col);
	pos = final->cursor_pos + ft_prompt_len(0) - (no_lignes * ws.ws_col);
	if (pos == ws.ws_col - 1)
		prev = pos + 1;
	else if (prev != 0 && pos == 0)
	{
		no_lignes--;
		pos = prev;
		prev = 0;
	}
	if (pos != 0)
		pos--;
	tputs(tgoto(tgetstr("cm", NULL), pos, no_lignes + ft_get_line_num(0))
			, 1, ft_putchar_term);
	return ;
}

static char		*ft_insert_char(t_input *final, char *input)
{
	struct winsize	ws;
	char		*begin;
	char		*insert;
	char		*end;
	char		*result;

	if (ioctl(0, TIOCGWINSZ, &ws) == -1)
		ft_putstr_fd("ft_insert_char\n", 2);
	begin = ft_strdup(final->result);
	insert = input;
	end = ft_strdup(&final->result[final->cursor_pos - 1]);
	begin[final->cursor_pos - 1] = '\0';
	result = ft_strjoin(begin, insert);
	result = ft_strjoin(result, end);
	final->cursor_max += ft_strlen(input);
	final->cursor_pos += ft_strlen(input);
	return (result);
}

static char		*ft_delete_char(t_input *final)
{
	char	*tmp;

	tmp = ft_strdup(final->result);
	tmp[final->cursor_pos - 2] = '\0';
	tmp = ft_strjoin(tmp, final->result + final->cursor_pos - 1);
	ft_free(final->result);
	final->result = ft_strdup(tmp);
	ft_free(tmp);
	final->cursor_pos -= 1;
	final->cursor_max -= 1;
	return (final->result);
}

/* /!\ 26L */

char			*print_word(t_input *final, char *input)
{
	int	len;

	if (input)
	{
		if (final->cursor_pos != final->cursor_max && input[0] != '\n'
			&& input[0] != 127 && input[0] != 8)
			final->result = ft_insert_char(final, input);
		else if (input[0] != '\n' && input[0] != 127 && input[0] != 8)
		{
			final->result = ft_strjoin(final->result, input);
			len = ft_strlen(input);
			final->cursor_max += (final->cursor_max == 0) ? len + 1 : len;
			final->cursor_pos = final->cursor_max;
		}
		else if (input[0] == 127 && final->cursor_pos > 1)
			final->result = ft_delete_char(final);
		ft_clear_line(final);
		tputs(tgetstr("rc", NULL), 1, ft_putchar_term);
		tputs(tgetstr("ce", NULL), 1, ft_putchar_term);
		ft_putstr(final->result);
		if (input[0] != '\n')
			ft_place_cursor(final);
		else
			ft_putstr("\n");
	}
	return (final->result);
}
