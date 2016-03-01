/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erobert <erobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 15:31:41 by erobert           #+#    #+#             */
/*   Updated: 2013/11/21 15:48:47 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int	quo;
	int	mod;

	if (n > 9)
	{
		quo = n / 10;
		ft_putnbr_fd(quo, fd);
		mod = n % 10;
		ft_putchar_fd(mod + '0', fd);
	}
	else if ((n > -1) && (n < 10))
		ft_putchar_fd(n + '0', fd);
	else
	{
		ft_putchar_fd('-', fd);
		ft_putnbr_fd(-n, fd);
	}
}
