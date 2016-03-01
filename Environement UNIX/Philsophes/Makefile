#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: erobert <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/09/27 13:33:19 by erobert           #+#    #+#              #
#    Updated: 2014/05/11 19:07:13 by hdezier          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = philo
FILES = ft_mlx_init.c ft_put_pixel_to_image.c ft_draw_state.c \
		ft_check_state.c ft_philosopher_init.c ft_drop_stick.c main.c
SRCS = $(addprefix srcs/, $(FILES))
OBJS = $(SRCS:srcs/%.c=objs/%.o)
TMPS = $(SRCS:.c=.c~) Makefile~ srcs/philo.h~
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LFLAGS = -L./libft/ -lft -lpthread -L/usr/X11/lib -lXext -lX11 -lmlx

.PHONY: all clean objs_dir fclean re

.SILENT: objs_dir

all: objs_dir $(NAME)

$(NAME): $(OBJS)
	make -C libft/
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LFLAGS)

objs/%.o : srcs/%.c
	$(CC) $(CFLAGS) -Iinc -I./libft -o $@ -c $^

objs_dir:
	mkdir -p objs

clean:
	make -C libft/ clean
	/bin/rm -f $(OBJS) $(TMPS)
	/bin/rm -rf objs

fclean: clean
	make -C libft/ fclean
	/bin/rm -f $(NAME)

re: fclean all
