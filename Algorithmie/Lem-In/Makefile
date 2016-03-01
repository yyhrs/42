#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: erobert <erobert@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/12/17 17:24:53 by erobert           #+#    #+#              #
#    Updated: 2014/03/12 16:12:36 by erobert          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = lem-in
FILES = ft_getcoord.c ft_getrooms.c ft_getcolony.c \
		ft_dijkstra.c ft_move_colony.c main.c
SRCS = $(addprefix srcs/, $(FILES))
OBJS = $(SRCS:srcs/%.c=objs/%.o)
TMPS = $(SRCS:.c=.c~) Makefile~ srcs/lemin.h~
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LFLAGS = -L./libft/ -lft

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
