# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/04/23 12:31:26 by ebaudet           #+#    #+#              #
#    Updated: 2014/04/23 12:44:50 by ebaudet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= nm_otool

NM			= nm
F_NM		= nm.c
SRC_NM		= $(addprefix srcs/, $(F_NM))
OBJ_NM		= $(SRC_NM:src/%.c=.obj/%.o)

OTOOL		= otool
F_OTOOL		= otool.c
SRC_OTOOL	= $(addprefix srcs/, $(F_OTOOL))
OBJ_OTOOL	= $(SRC_OTOOL:src/%.c=.obj/%.o)

INC			= -I includes -I libft/includes
FLAGS		= -Wall -Wextra -Werror
LIB			= -L libft -lft
CC			= gcc

all: $(NAME)

$(NAME): createfolder $(OTOOL) $(NM)

$(OTOOL): $(OBJ_OTOOL)
	make -C libft
	$(CC) $(FLAGS) $(OBJ_OTOOL) -o $(OTOOL) $(INC) $(LIB)

$(NM): $(OBJ_NM)
	make -C libft
	$(CC) $(FLAGS) $(OBJ_NM) -o $(NM) $(INC) $(LIB)

.obj/%.o: src/%.c
	cc -c $< -o $@ $(FLAGS) $(INC)

createfolder:
	mkdir -p .obj

clean:
	rm -rf .obj

fclean: clean
	rm -f $(OTOOL) $(NM)

re: fclean all

.PHONY: all clean fclean re createfolder
