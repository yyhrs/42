/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemipc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erobert <erobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/26 16:28:17 by erobert           #+#    #+#             */
/*   Updated: 2014/05/29 15:55:02 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIPC_H
# define LEMIPC_H

# include <unistd.h>

# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define END "\033[0m"

# define HEIGHT 10
# define WIDTH 10
# define KEY 1138
# define SLEEP_T 25000
# define ALL 1

typedef union			u_sem
{
	int					val;
	struct semid_ds		*buf;
	unsigned short int	*array;
}						t_sem;

typedef struct			s_data
{
	char				*map;
	int					size;
	int					shmid;
	int					slot;
	int					master;
	int					semid;
	t_sem				sem;
}						t_data;

void					ft_putstr_fd(char const *s, int fd);
void					ft_putendl_fd(char const *s, int fd);
int						ft_shm_create(t_data *d);
int						ft_sem_create(t_data *d);
int						ft_print_result(char *s1, char *s2, int res);
int						ft_endgame(char *map);
int						ft_playgame(t_data *d);

#endif
