/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_clean.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaron <tcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/09 16:25:23 by tcaron            #+#    #+#             */
/*   Updated: 2014/02/09 16:25:23 by tcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../header.h"
#include "../libft.h"

static char			*ft_past_word(t_parse *final)
{
	char	*final_s;
	t_parse	*tmp;

	final_s = ft_strdup(final->word);
	ft_free(final->word);
	final_s = ft_strjoin(final_s, " \0");
	tmp = final;
	final = final->next;
	ft_free(tmp);
	while (final && final->word)
	{
		final_s = ft_strjoin(final_s, final->word);
		ft_free(final->word);
		final_s = ft_strjoin(final_s, " \0");
		tmp = final;
		final = final->next;
		ft_free(tmp);
	}
	if (final && final->next)
		ft_free(final->next);
	ft_free(final);
	return (final_s);
}

/* /!\ +26L  */

static t_parse		*ft_find_op(int j, int *i, char *buffer, t_parse *final)
{
	char	*tmp;

	if (j)
	{
		final = ft_add_word((tmp = ft_strsub(buffer, *i - j, j)), final);
		ft_free(tmp);
	}
	if (!buffer[*i])
		return (final);
	if (buffer[*i] == '|')
		final = ft_add_word("|\0", final);
	else if (buffer[*i] == ';')
		final = ft_add_word(";\0", final);
	else if (buffer[*i] == '>' && buffer[*i + 1] == '>')
	{
		final = ft_add_word(">>\0", final);
		(*i)++;
	}
	else if (buffer[*i] == '<' && buffer[*i + 1] == '<')
	{
		final = ft_add_word("<<\0", final);
		(*i)++;
	}
	else if (buffer[*i] == '>')
		final = ft_add_word(">\0", final);
	else if (buffer[*i] == '<')
		final = ft_add_word("<\0", final);
	else if (buffer[*i] == '$')
	{
		final = ft_add_word(ft_get_var(buffer + 1 + *i), final);
		while (!CHAR_END(buffer[*i]))
			(*i)++;
	}
	return (final);
}

static t_parse		*ft_split_buffer(char *buffer, t_parse *final)
{
	int	i;
	int	j;

	i = 0;
	while (buffer[i])
	{
		j = 0;
		while (buffer[i] && buffer[i] != ';'
				&& buffer[i] != '|' && buffer[i] != '\t'
				&& buffer[i] != ' ' && buffer[i] != '>'
				&& buffer[i] != '<' && buffer[i] != '$')
		{
			j++;
			i++;
		}
		final = ft_find_op(j, &i, buffer, final);
		i++;
	}
	return (final);
}

char				*ft_parse_clean(char *buffer)
{
	char	*new_buff;
	t_parse	*final;

	final = NULL;
	final = ft_split_buffer(buffer, final);
	new_buff = ft_past_word(final);
	return (new_buff);
}

