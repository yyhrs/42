/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keycatch_UD_WL.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaron <tcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/09 16:27:07 by tcaron            #+#    #+#             */
/*   Updated: 2014/02/09 16:27:07 by tcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <termcap.h>
#include <termios.h>
#include <sys/ioctl.h>
#include "../header.h"
#include "../libft.h"

#include <stdio.h>

/*
** ft_check_key_UD is used for moving in history.
*/

static char		*ft_check_key_UD(t_input *final, t_cmd *line)
{
	char	*tmp;

	tmp = ft_get_current_line(line);
	ft_free(final->result);
	final->result = ft_strdup(tmp);
	if (!final->result || (final->result && final->result[0] == '\0'))
	{
		ft_free(final->result);
		final->result = ft_strdup(final->save);
	}
	ft_clear_line(final);
	tputs(tgetstr("rc", NULL), 1, ft_putchar_term);
	tputs(tgetstr("ce", NULL), 1, ft_putchar_term);
	ft_putstr(final->result);
	final->cursor_max = ft_strlen(final->result) + 1;
	final->cursor_pos = final->cursor_max;
	return (final->result);
}

static void		ft_execute_value_key(int value, t_input *final, char *input)
{
	ft_strclr(input);
	tputs(tgetstr("rc", NULL), 1, ft_putchar_term);
	if (value == 1)
		ft_prev_word(final);
	if (value == 2)
		ft_next_word(final);
	if (value == 3)
		ft_next_line(final);
	if (value == 4)
		ft_prev_line(final);
	return ;
}

/*
** Moving word by word or line by line
*/

static void		ft_check_key_WL(char *input, t_input *final)
{
	int	value;

	value = 0;
	if (input[0] == 0x1B && input[1] == 0x1B && input[2] == 0x5B
		&& input[3] == 0x44 && input[4] == '\0')
		value = 1;
	else if (input[0] == 0x1B && input[1] == 0x1B && input[2] == 0x5B
		&& input[3] == 0x43 && input[4] == '\0')
		value = 2;
	else if (input[0] == 0x1B && input[1] == 0x1B && input[2] == 0x5B
		&& input[3] == 0x42 && input[4] == '\0')
		value = 3;
	else if (input[0] == 0x1B && input[1] == 0x1B && input[2] == 0x5B
		&& input[3] == 0x41 && input[4] == '\0')
		value = 4;
	if (value)
	{
		ft_execute_value_key(value, final, input);
		final->cursor_max -= (value <= 2) ? 0 : 1;
		if (final->cursor_pos > final->cursor_max)
			final->cursor_pos = final->cursor_max;
		input[0] = '\0';
	}
	return ;
}

static int		ft_check_homend(char *input, t_input *final)
{
	if (input)
	{
		if (input[2] == 0x48)
		{
			final->cursor_pos = 1;
			ft_place_cursor(final);
			return (1);
		}
		else
		{
			final->cursor_pos = final->cursor_max;
			input[0] = '\0';
		}
	}
	return (0);
}

char			*ft_check_key(char *input, t_input *final, t_cmd *line)
{
	int			value;
	char		*result;

	if (input)
	{
		if (ft_key_up_or_down(input))
			return (ft_check_key_UD(final, line));
		else if ((value = ft_key_left_or_rigth(input)))
			return (ft_check_key_LR(final, value));
		else if (HOMEND && ft_check_homend(input, final))
			return (final->result);
		else if (input[0] == 0x1B && input[1] == '\0')
		{
			if (ft_strcmp((result = ft_CCP_seq(final)), final->result) == 0)
				return (result);
			else
			{
				ft_free(final->result);
				final->result = ft_strdup(result);
				input[0] = '\0';
				ft_free(result);
			}
		}
		else if (input[0] == 0x09 && input[1] == '\0')
			ft_completion(input, final);
		ft_check_key_WL(input, final);
	}
	final->result = print_word(final, input);
	return (final->result);
}
