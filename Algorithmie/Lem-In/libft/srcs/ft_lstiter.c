/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erobert <erobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/23 14:46:14 by erobert           #+#    #+#             */
/*   Updated: 2013/12/16 12:43:07 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(list_t *lst, void (*f)(list_t *elem))
{
	while (lst)
	{
		(*f)(lst);
		lst = lst->next;
	}
}
