/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erobert <erobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/21 11:36:38 by erobert           #+#    #+#             */
/*   Updated: 2014/03/12 18:02:05 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include <limits.h>

typedef struct		s_lst
{
	int				mode;
	int				numero;
	char			*room[3];
	struct s_lst	*next;
}					t_lst;

typedef struct		s_colony
{
	char			*stock;
	int				nb_ants;
	int				ants;
	int				start;
	int				end;
	int				nb_rooms;
	int				**nodes;
}					t_colony;

int		ft_strcmp(const char *s1, const char *s2);
int		ft_atoi(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_putstr_fd(char const *s, int fd);
void	ft_putendl_fd(char const *s, int fd);
void	ft_putnbr_fd(int n, int fd);
int		ft_getline(int const fd, char **line);
int		ft_getcoord(t_lst **lst, char *line, int mode);
int		ft_getrooms(t_colony *colony, t_lst **lst);
t_lst	*ft_getcolony(t_colony *colony);
int		ft_dijkstra(int **nodes, int nb_rooms, int src, int end);
int		ft_move_colony(t_colony *c, t_lst **tab);

#endif
