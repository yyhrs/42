/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaron <tcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/09 16:26:33 by tcaron            #+#    #+#             */
/*   Updated: 2014/02/18 14:56:31 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <termcap.h>
#include <termios.h>
#include "../header.h"
#include "../libft.h"

int				ft_prompt_len(int size)
{
	static int	len = 0;

	if (size != 0)
		len = size;
	return (len);
}

static char		*ft_get_user(void)
{
	char	*result;

	if ((result = getenv("USER")) != NULL)
		return (ft_strdup(result));
	else
		return (ft_strdup("N/A\0"));
}

/*
** Loocking for user
*/

static char		*ft_parse_prompt(char *path)
{
	char	*user;
	char	*result;
	char	*stock;
	char	*tmp;

	user = ft_get_user();
	result = ft_strdup("\033[1;34m\0");
	result = ft_strjoin(result, user);
	result = ft_strjoin(result, "\033[0m:\0");
	tmp = path;
	while (*path)
	{
		if (*path == '/')
			stock = path + 1;
		path++;
	}
	result = ft_strjoin(result, stock);
	result = ft_strjoin(result, " $> \0");
	ft_free(user);
	ft_free(tmp);
	return (result);
}

/*
** Less 11 because ANSI escape code represent 11 characters.
** ft_get_line_num send the current line to a function.
*/

void			ft_prompt(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	path = ft_parse_prompt(path);
	ft_putstr(path);
	ft_free(path);
	ft_prompt_len(ft_strlen(path) - 11);
	tputs(tgetstr("sc", NULL), 1, ft_putchar_term);
	ft_get_line_num(1);
}
