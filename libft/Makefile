#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/11/21 12:00:46 by ebaudet           #+#    #+#              #
#    Updated: 2014/02/08 20:18:24 by ebaudet          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME 	= libft.a
SRCS 	= ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c \
		ft_memchr.c ft_memcmp.c ft_strlen.c ft_strdup.c ft_strcpy.c \
		ft_strncpy.c ft_strcat.c ft_strncat.c ft_strlcat.c ft_strchr.c \
		ft_strrchr.c ft_strstr.c ft_strnstr.c ft_strcmp.c ft_strncmp.c \
		ft_atoi.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
		ft_isprint.c ft_toupper.c ft_tolower.c ft_strmap.c ft_strmapi.c \
		ft_memalloc.c ft_memdel.c ft_strnew.c ft_strdel.c ft_strclr.c \
		ft_striter.c ft_striteri.c ft_strequ.c ft_strnequ.c ft_strsub.c \
		ft_strjoin.c ft_strtrim.c ft_strsplit.c ft_itoa.c \
		ft_putchar.c ft_putstr.c ft_putendl.c ft_putnbr.c \
		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
		get_next_line.c
DIRSRC	= $(addprefix ./ ,$(SRCS))
OBJS	= ${SRCS:%.c=.obj/%.o}
INC		= ./includes/
FLAGS	= -Wall -Wextra -Werror -fno-builtin -fno-stack-protector -pedantic -ansi
DEBUGFLG = -v -da -Q
CC		= gcc
AR		= ar rc
RANLIB	= ranlib

all: $(NAME)
	
$(NAME): $(OBJS)
	@echo ""
	@$(AR) $(NAME) $(OBJS)
	@$(RANLIB) $(NAME)
	@echo "création de $(NAME)"

.obj/%.o: %.c
	@mkdir -p .obj
	@$(CC) -c $< -o $@ $(FLAGS) -I $(INC)
	@printf .

clean:
	rm -rf .obj

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
