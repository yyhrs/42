/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erobert <erobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/05 10:31:01 by erobert           #+#    #+#             */
/*   Updated: 2014/05/11 22:34:44 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# define SEC 1000000
# define MAX_LIFE 42
# define EAT_T 5
# define REST_T 5
# define THINK_T 2
# define TIMEOUT 42

typedef union	u_color
{
	int			c;
	char		rgba[4];
}				t_color;

typedef struct	s_img
{
	void		*ptr;
	int			size[2];
	char		*data;
	int			bpp;
	int			line;
	int			endian;
}				t_img;

typedef struct	s_data
{
	void		*mlx_ptr;
	void		*mlx_win;
	int			size[2];
	t_img		img;
}				t_data;

typedef struct	s_philosopher
{
	int			id;
	int			hp;
	t_data		*d;
	int			state;
}				t_philosopher;

void			*ft_memcpy(void *s1, const void *s2, size_t n);
void			ft_putstr_fd(char const *s, int fd);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putnbr_fd(int n, int fd);
int				ft_mlx_init(t_data *d);
void			ft_put_pixel_to_image(t_data *d, int x, int y, int c);
void			ft_philosopher_init(t_philosopher *p, t_data *d);
void			ft_drop_stick(int id, int *sticks, pthread_mutex_t *lock);
void			ft_drop_hp(int *sticks, t_philosopher *p, int id);
void			ft_draw_state(t_philosopher *p);
void			ft_check_state(t_philosopher *p, int *sticks);

#endif
