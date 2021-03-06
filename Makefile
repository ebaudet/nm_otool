# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/04/23 12:31:26 by ebaudet           #+#    #+#              #
#    Updated: 2019/12/19 17:20:13 by ebaudet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= nm_otool

F_UTILS		= ft_error.c ft_pow.c ft_secure.c ft_puthex.c endian_swap.c \
			ft_gethex.c int_to_hexa.c ft_in_array.c ft_is_my_arch.c \
			ft_putprint.c
SRC_UTILS	= $(addprefix srcs/utils/, $(F_UTILS))
OBJ_UTILS	= $(SRC_UTILS:srcs/utils/%.c=.obj/utils/%.o)

NM			= ft_nm
F_NM		= nm.c nm_32.c nm_64.c nm_fat.c flag_handler.c symtable.c \
			symbol.c list_add.c print_output.c handle_arch.c compare.c \
			handle_type.c handle_file.c
SRC_NM		= $(addprefix srcs/nm/, $(F_NM))
OBJ_NM		= $(SRC_NM:srcs/nm/%.c=.obj/nm/%.o)

OTOOL		= ft_otool
F_OTOOL		= get_addr_endian.c ot_type_handler.c get_segment_command_nsects.c \
			otool.c loop_lc_segment.c print_section.c obed.c set_arch.c \
			ot_binary_handler.c sizeof_mach_header.c ot_fat_handler.c \
			sizeof_section.c ot_flag.c sizeof_segment_command.c \
			ot_put_achitecture_name.c treatment_file.c
SRC_OTOOL	= $(addprefix srcs/otool/, $(F_OTOOL))
OBJ_OTOOL	= $(SRC_OTOOL:srcs/otool/%.c=.obj/otool/%.o)

INC			= -I includes -I libft/includes -I libft/ft_printf
FLAGS		= -Wall -Wextra -Werror
LIB			= -L libft -lft
DEBUGFLG	= -fsanitize=address -g3
# DEBUGFLG	=
CC			= cc

all: $(NAME)

$(NAME): $(OTOOL) $(NM)

$(OTOOL): make_libft $(OBJ_UTILS) $(OBJ_OTOOL)
	@echo ""
	$(CC) $(FLAGS) $(OBJ_UTILS) $(OBJ_OTOOL) -o $(OTOOL) $(INC) $(LIB) $(DEBUGFLG)
	@echo "> Compilation \033[35m$(OTOOL)\033[m [\033[32mDONE\033[m]\n"

$(NM): make_libft $(OBJ_UTILS) $(OBJ_NM)
	@echo ""
	$(CC) $(FLAGS) $(OBJ_UTILS) $(OBJ_NM) -o $(NM) $(INC) $(LIB) $(DEBUGFLG)
	@echo "> Compilation \033[35m$(NM)\033[m [\033[32mDONE\033[m]\n"

.obj/%.o: srcs/%.c
	@mkdir -p .obj .obj/utils .obj/nm .obj/otool
	@$(CC) -c $< -o $@ $(FLAGS) $(INC) $(DEBUGFLG)
	@echo -n .

make_libft:
	@echo "Compilation de la libft :"
	@make -C libft
	@echo ""

clean:
	rm -rf .obj
	make -C libft clean

fclean: clean
	rm -f $(OTOOL) $(NM)
	make -C libft fclean

re: fclean all

test:
	make
	./ddiff.sh ./ft_nm nm  /usr/bin/*
	./ddiff.sh ./ft_otool "otool -t" /usr/bin/a*
	./ddiff.sh ./ft_otool "otool -t" /usr/bin/appletviewer

test-nm:
	@echo "make && ./ddiff.sh ./ft_nm nm  /usr/bin/*"
	make && ./ddiff.sh ./ft_nm nm  /usr/bin/*

test-otool:
	@echo 'make && ./ddiff.sh ./ft_otool "otool -t" /usr/bin/a*'
	make && ./ddiff.sh ./ft_otool "otool -t" /usr/bin/a*

test-otool1:
	@echo 'make && ./ddiff.sh ./ft_otool "otool -t" /usr/bin/appletviewer'
	make && ./ddiff.sh ./ft_otool "otool -t" /usr/bin/appletviewer

norminette:
	norminette srcs includes libft

gdb: make_libft
	cc -g $(FLAGS) $(SRC_OTOOL) -o $(OTOOL) $(INC) $(LIB)
	cc -g $(FLAGS) $(SRC_NM) -o $(NM) $(INC) $(LIB)

.PHONY: all clean fclean re gdb
