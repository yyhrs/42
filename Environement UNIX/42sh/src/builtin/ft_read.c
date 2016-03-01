/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdezier <hdezier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/17 15:58:19 by hdezier           #+#    #+#             */
/*   Updated: 2014/02/17 15:58:20 by hdezier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"
#include "../libft.h"
#include <stdlib.h>
#include <unistd.h>

static void	ft_init_list(char *key, char *data, t_list **tab, int n)
{
	t_list	*result;
	t_list	*tmp;

	result = (t_list *)malloc(sizeof(t_list));
	result->data = data;
	result->key = key;
	tmp = tab[n];
	while (tmp)
	{
		if (!ft_strcmp(key, tmp->key))
		{
			tmp->data = data;
			return ;
		}
		tmp = tmp->next;
	}
	result->next = tab[n];
	tab[n] = result;
}

static void	ft_init_tab_list(t_list ***tab)
{
	int		i;

	i = -1;
	(*tab) = (t_list **)malloc(HASH_SIZE * sizeof(t_list *));
	while (++i < HASH_SIZE)
		(*tab)[i] = NULL;
}

t_list		**ft_add_data(char *s)
{
	static t_list	**tab = NULL;
	char			buf[BUFF_SIZE];
	int				ret;

	if (!s)
		return (tab);
	if (!tab)
		ft_init_tab_list(&tab);
	ft_restore();
	ret = read (0, buf, BUFF_SIZE);
	buf[ret - 1] = '\0';
	ft_non_canonical();
	ft_init_list(s, ft_strdup(buf), tab, ft_hash(s));
	return (NULL);
}

void		ft_read(t_seq *seq)
{
	int		size;
	char	*result;

	size = 0;
	if (CHAR_END(seq->args[0]))
		ft_add_data("REPLY");
	else
	{
		while (!CHAR_END(seq->args[size]))
			size++;
		result = (char *)malloc((size + 1) * sizeof(char));
		result[size] = '\0';
		while (--size >= 0)
			result[size] = seq->args[size];
		ft_add_data(result);
	}
}
