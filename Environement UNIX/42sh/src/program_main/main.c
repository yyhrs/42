/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaron <tcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/09 16:26:22 by tcaron            #+#    #+#             */
/*   Updated: 2014/02/18 17:48:54 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <termcap.h>
#include <termios.h>
#include <unistd.h>
#include "../header.h"
#include "../libft.h"

int				ft_get_id(int more)
{
	static int	id = 0;

	if (more)
	{
		id++;
		return (id);
	}
	else
		return (id);
}

static void		ft_init_line(t_cmd *line)
{
	line->origin = NULL;
	line->clean = NULL;
	line->seq = NULL;
	line->next = NULL;
	line->prev = NULL;
	line->id = 0;
}

static void		ft_loop(void)
{
	t_cmd	line;
	t_cmd	*current;

	ft_init_line(&line);
	current = &line;
	ft_cleaner(NULL, &line, 0);
	while (1)
	{
		while (current->id != ft_get_id(0))
		{
			if (!current->next)
				ft_add_elem(current);
			current = current->next;
		}
		ft_prompt();
		current->origin = ft_get_input(current);
		current->clean = ft_parse_clean(current->origin);
		current->seq = ft_lexer(current->clean);
		ft_exec(current->seq);
		ft_get_id(1);
		ft_current_id(2);
	}
}

int				main(void)
{
	char	*term;

	if ((term = getenv("TERM")) == NULL)
	{
		ft_putstr_fd("Error with getenv\n", 2);
		return (-1);
	}
	if (tgetent(NULL, term) != 1)
	{
		ft_putstr_fd("Error with tgetent\n", 2);
		return (-1);
	}
	ft_init_path();
	ft_signal();
	ft_non_canonical();
	ft_loop();
	ft_restore();
	return (0);
}
