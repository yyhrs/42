/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_first_control.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaron <tcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/09 16:26:41 by tcaron            #+#    #+#             */
/*   Updated: 2014/02/09 16:26:42 by tcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int		ft_first_control_syntax(char *input)
{
	int		c;
	int		pipe;

	c = pipe = 0;
	while (*input)
	{
		if (CHAR_S(*input) && !c)
			c = *input;
		else if (c && *input == c)
			c = 0;
		else if (*input == '|' || *input == '\\')
			pipe = 1;
		else if (pipe && *input != ' ')
			pipe = 0;
		input++;
	}
	return (c || pipe);
}
