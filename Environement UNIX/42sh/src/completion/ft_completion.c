
#include <stdlib.h>
#include <dirent.h>
#include <termcap.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "../header.h"
#include "../libft.h"

static char		*current_path = NULL;

void			ft_get_home(void)
{
	extern char	**environ;
	char	*tmp;

	while (ft_strncmp(*environ, "HOME=", 5) != 0)
		(environ)++;
	tmp = ft_strdup(&current_path[1]);
	free(current_path);
	current_path = ft_strjoin(ft_strdup((*environ) + 5), tmp);
}

static void		ft_make_choice(t_comp *list, t_input *final, char *word)
{
	int			i;
	static int	check = 0;

	i = 0;
	if (list && list->next == NULL)
	{
		while (list->choice[i] == word[i])
			i++;
		final->result = ft_strjoin(final->result, &list->choice[i]);
		final->cursor_max += ft_strlen(&list->choice[i]);
		final->cursor_pos = final->cursor_max;
		if (check)
		{
			ft_putstr("\033[B\033[2K\033[A");
			check--;
		}
	}
	else
	{
		ft_print_choice(list, 0);
		check += (check == 0) ? 1 : 0;
	}
	ft_free_list_comp(list);
}

static t_comp	*ft_add_elem_list(char *choice, t_comp *list, int id)
{
	t_comp	*elem;
	t_comp	*start;

	elem = (t_comp *)malloc(sizeof(t_comp));
	ft_error_malloc((t_comp *)elem, "Error in ft_completion.c");
	elem->choice = ft_strdup(choice);
	elem->id = id;
	elem->next = NULL;
	elem->prev = NULL;
	start = list;
	if (!list)
		return (elem);
	else
	{
		while (list->next != NULL)
			list = list->next;
		list->next = elem;
		return (start);
	}
}

static t_comp	*ft_get_list(char *tofind)
{
	t_comp			*result;
	DIR				*d;
	struct dirent	*dir;
	int				id;

	if (current_path[0] == '~')
		ft_get_home();
	d = opendir(current_path);
	result = NULL;
	id = -1;
	if (d)
	{
		while ((dir = readdir(d)))
		{
			if (ft_strncmp(dir->d_name, tofind, ft_strlen(tofind)) == 0
				|| tofind[0] == 0)
			{
				result = ft_add_elem_list(dir->d_name, result, ++id);
			}
		}
		closedir(d);
	}
	return (result);
}

void		ft_completion(char *input, t_input *final)
{
	char	*word;
	t_comp	*list;
	int		i;
	int		j;

	i = (int)ft_strlen(final->result);
	if (current_path)
			free(current_path);
	while (i > 0 && (final->result[i] != ' ' && final->result[i] != '/'))
		i--;
	word = (final->result[i] == '/') ? &final->result[i + 1] : &final->result[i];
	if (final->result[i] == '/')
	{
		j = i;
		while (j > 0 && final->result[j] != ' ')
			j--;
		j -= (j > 0 && final->result[j] == ' ') ? 1 : 0;
		current_path = ft_strsub(final->result, j, i - j);
	}
	else
		current_path = ft_strdup("./");
	list = ft_get_list(word);
	ft_make_choice(list, final, word);
	ft_strclr(input);
}
