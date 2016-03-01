# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbernand <rbenand@student.42.fr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/10/16 15:08:59 by rbernand          #+#    #+#              #
#    Updated: 2016/02/09 16:16:52 by erobert          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=Corewar
ASM=asm
VM=corewar
CC=	cc
FLAGS=-Wall -Wextra -Werror -g
LIBFT=libft/
LIBVECT=libvect/
LIBMLX11=minilibx/
LIBMLXOSX=minilibxosx/
LIBOPT=libopt/
INCLUDES=include/
DIROBJ=obj/
DIRLIB=lib/
DIRSRC=src/
DIRBIN=bin/
DIRCOMMON=common/
DIRVM=vm/
DIRASM=asm/
SRC_COMMON=\
	op.c \
	list_new.c \
	list_push_front.c \
	list_delete.c \
	list_push_back.c \
	list_iter.c \
	list_back.c \
	list_count.c \
	ft_strip_chrs.c \
	swap_uint.c \
	get_op_by_id.c
SRC_ASM=\
	main.c \
	add_label.c \
	parse.c \
	get_octet_code.c \
	is_correct_label.c \
	add_instruction.c \
	put_hexa.c \
	store_params.c \
	link_labels.c \
	write_header.c \
	get_instruction_param.c
SRC_VM=\
	main.c \
	parse_argument.c \
	load_players.c \
	alloc_memory.c \
	dump_memory.c \
	dump_ncurses.c \
	put_players_on_memory.c \
	new_process.c \
	play.c \
	live.c \
	sti.c \
	and.c \
	zjmp.c \
	lfork.c \
	sfork.c \
	lld.c \
	ld.c \
	add.c \
	sub.c \
	ldi.c \
	or.c \
	xor.c \
	st.c \
	aff.c \
	lldi.c \
	read_memory.c \
	write_memory.c \
	get_register_value.c \
	get_binary_op_value.c \
	last_live.c \
	init_ncurses.c
OBJ_ASM=$(SRC_ASM:%.c=$(DIROBJ)$(DIRASM)%.o)
OBJ_VM=$(SRC_VM:%.c=$(DIROBJ)$(DIRVM)%.o)
OBJ_COMMON=$(SRC_COMMON:%.c=$(DIROBJ)$(DIRCOMMON)%.o)

all: init $(NAME) end

init:
	@mkdir -p $(DIRBIN)
	@mkdir -p $(DIRLIB)
	@mkdir -p $(DIROBJ)
	@mkdir -p $(DIROBJ)$(DIRASM)
	@mkdir -p $(DIROBJ)$(DIRCOMMON)
	@mkdir -p $(DIROBJ)$(DIRVM)
	@git submodule init
	@git submodule update
	@make -s -C $(LIBFT)
	@cd $(DIRLIB) && ln -f ../$(LIBFT)/libft.a .
	@ln -f $(LIBFT)includes/libft.h $(INCLUDES)/

end:
	@printf "\r\033[2K\033[1;36m%-20s\033[0;32m[Ready]\033[0m\n" $(NAME)

$(NAME): $(OBJ_COMMON) $(ASM) $(VM)

.PHONY: libft clean flcean re

libft:
	@make -s -C $(LIBFT)


$(VM): $(OBJ_VM) $(OBJ_COMMON)
	@printf "\r\033[2KCompiling %s" $@
	@$(CC) $(FLAGS) -o $(DIRBIN)$@ $^ -I$(INCLUDES) -L$(DIRLIB) -lft -lncurses
	@ln -f $(DIRBIN)$@ $@

$(ASM): $(OBJ_ASM) $(OBJ_COMMON)
	@printf "\r\033[2KCompiling %s" $@
	@$(CC) $(FLAGS) -o $(DIRBIN)$@ $^ -I$(INCLUDES) -L$(DIRLIB) -lft
	@ln -f $(DIRBIN)$@ $@

$(DIROBJ)$(DIRASM)%.o: $(DIRSRC)$(DIRASM)%.c
	@printf "\r\033[2KLinking %s" $@
	@$(CC) $(FLAGS) -o $@ -c $< -I$(INCLUDES)

$(DIROBJ)$(DIRCOMMON)%.o: $(DIRSRC)$(DIRCOMMON)%.c
	@printf "\r\033[2KLinking %s" $@
	@$(CC) $(FLAGS) -o $@ -c $< -I$(INCLUDES)

$(DIROBJ)$(DIRVM)%.o: $(DIRSRC)$(DIRVM)%.c
	@printf "\r\033[2KLinking %s" $@
	@$(CC) $(FLAGS) -o $@ -c $< -I$(INCLUDES)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -rf $(ASM)
	@rm -rf $(VM)
	@rm -rf $(DIROBJ)
	@rm -rf $(DIRLIB)

re: fclean all
