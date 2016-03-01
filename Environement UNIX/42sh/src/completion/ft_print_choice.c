
#include <unistd.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include "../header.h"
#include "../libft.h"

/*
** Annoncer le nombres de choix restant ?
*/

void	ft_free_list_comp(t_comp *list)
{
	t_comp	*tmp;

	tmp = list;
	while (list)
	{
		free(list->choice);
		tmp = list;
		list = list->next;
		free(tmp);
	}
}

void	ft_do_print(t_comp *start, int j)
{
	int	i;

	i = -1;
	while (start && ++i != j)
	{
		if (i == 0)
			ft_putstr("\n\033[2K");
		ft_putstr(start->choice);
		ft_putstr(" ");
		start = start->next;
	}
	if (start && start->next != NULL)
		ft_putstr("\033[47m\033[30m->\033[0m");
	else if (start)
		ft_putstr(start->choice);
	return ;
}

void	ft_print_choice(t_comp *list, int i)
{
	struct winsize	ws;
	int				max;
	int				j;
	t_comp			*start;

	j = 20;
	max = 0;
	start = list;
	if (ioctl(0, TIOCGWINSZ, &ws) == -1)
		ft_putstr_fd("ft_print_choice\n", 2);
	while (list && j && i != j)
	{
		max += ft_strlen(list->choice) + 1;
		if (++i == j && max > ws.ws_col)
		{
			i = 0;
			max = 0;
			list = start;
			j--;
		}
		else
			list = list->next;
	}
	ft_do_print(start, j - 1);
}
