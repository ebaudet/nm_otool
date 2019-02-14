# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/04/23 12:31:26 by ebaudet           #+#    #+#              #
#    Updated: 2019/02/14 16:58:40 by ebaudet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= nm_otool

NM			= ft_nm
F_NM		= ft_pow.c ft_puthex.c ft_error.c endian_swap.c nm.c
SRC_NM		= $(addprefix srcs/, $(F_NM))
OBJ_NM		= $(SRC_NM:srcs/%.c=.obj/%.o)

OTOOL		= ft_otool
F_OTOOL		= ft_pow.c ft_puthex.c ft_error.c otool.c
SRC_OTOOL	= $(addprefix srcs/, $(F_OTOOL))
OBJ_OTOOL	= $(SRC_OTOOL:srcs/%.c=.obj/%.o)

INC			= -I includes -I libft/includes -I libft/ft_printf
FLAGS		= -Wall -Wextra -Werror
LIB			= -L libft -lft
DEBUGFLG	= -fsanitize=address -g3
DEBUGFLG	=
CC			= cc

all: $(NAME)

$(NAME): $(OTOOL) $(NM)

$(OTOOL): make_libft $(OBJ_OTOOL)
	$(CC) $(FLAGS) $(OBJ_OTOOL) -o $(OTOOL) $(INC) $(LIB) $(DEBUGFLG)
	@echo "> Compilation \033[35m$(OTOOL)\033[m [\033[32mDONE\033[m]\n"

$(NM): make_libft $(OBJ_NM)
	$(CC) $(FLAGS) $(OBJ_NM) -o $(NM) $(INC) $(LIB) $(DEBUGFLG)
	@echo "> Compilation \033[35m$(NM)\033[m [\033[32mDONE\033[m]\n"

.obj/%.o: srcs/%.c
	@mkdir -p .obj
	$(CC) -c $< -o $@ $(FLAGS) $(INC)

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

gdb: make_libft
	cc -g $(FLAGS) $(SRC_OTOOL) -o $(OTOOL) $(INC) $(LIB)
	cc -g $(FLAGS) $(SRC_NM) -o $(NM) $(INC) $(LIB)

.PHONY: all clean fclean re gdb
