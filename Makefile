# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/04/23 12:31:26 by ebaudet           #+#    #+#              #
#    Updated: 2014/04/23 13:27:14 by ebaudet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= nm_otool

NM			= ft_nm
F_NM		= nm.c
SRC_NM		= $(addprefix srcs/, $(F_NM))
OBJ_NM		= $(SRC_NM:srcs/%.c=.obj/%.o)

OTOOL		= ft_otool
F_OTOOL		= otool.c
SRC_OTOOL	= $(addprefix srcs/, $(F_OTOOL))
OBJ_OTOOL	= $(SRC_OTOOL:srcs/%.c=.obj/%.o)

INC			= -I includes -I libft/includes
FLAGS		= -Wall -Wextra -Werror
LIB			= -L libft -lft
CC			= gcc

all: $(NAME)

$(NAME): $(OTOOL) $(NM)

$(OTOOL): make_libft $(OBJ_OTOOL)
	$(CC) $(FLAGS) $(OBJ_OTOOL) -o $(OTOOL) $(INC) $(LIB)

$(NM): make_libft $(OBJ_NM)
	$(CC) $(FLAGS) $(OBJ_NM) -o $(NM) $(INC) $(LIB)

.obj/%.o: srcs/%.c
	@mkdir -p .obj
	$(CC) -c $< -o $@ $(FLAGS) $(INC)

make_libft:
	@echo "Compilation de la libft :"
	@make -C libft

clean:
	rm -rf .obj

fclean: clean
	rm -f $(OTOOL) $(NM)

re: fclean all

.PHONY: all clean fclean re
