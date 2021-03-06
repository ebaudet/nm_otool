# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/11/21 12:00:46 by ebaudet           #+#    #+#              #
#    Updated: 2019/04/29 20:14:10 by ebaudet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= libft.a
LIBSRCS = ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c \
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
		get_next_line.c ft_concat.c ft_strreverse.c ft_lutohex.c \
		ft_atod.c ft_isspace.c ft_abs.c ft_fabs.c ft_dtoa.c ft_lutooct.c \
		ft_max.c ft_min.c ft_lutobin.c ft_ldtoa.c
PRINTSRCS = ft_printf.c pf_getsstr.c pf_type_float.c pf_type_hexa.c pf_type_int.c \
		pf_type_other.c pf_type_text.c pf_handler.c pf_handler_2.c \
		pf_functions.c pf_get_dec_lenght.c pf_params.c pf_buffer.c
SRCS	= $(LIBSRCS) ${PRINTSRCS:%.c=ft_printf/%.c}
OBJS	= ${SRCS:%.c=.obj/%.o}
INC		= -I ./includes/ -I ./ft_printf/
FLAGS	= -Wall -Wextra -Werror -fno-builtin -fno-stack-protector -pedantic -ansi
FLAGS	= -Wall -Wextra -Werror
# DEBUGFLG = -fsanitize=address -g3
DEBUGFLG =
LIB		=  -L . libft.a
CC		= gcc
AR		= ar rc
RANLIB	= ranlib

all: $(NAME)

$(NAME): $(OBJS)
	@$(AR) $(NAME) $(OBJS)
	@$(RANLIB) $(NAME)
	@echo "\n\n > Compilation \033[36mlibft\033[m [\033[32mDONE\033[m]"

.obj/%.o: %.c
	@mkdir -p .obj
	@mkdir -p .obj/ft_printf
	@$(CC) -c $< -o $@ $(FLAGS) $(INC) $(DEBUGFLG)
	@echo -n .

clean:
	@rm -rf .obj

fclean: clean
	@rm -f $(NAME)

re: fclean all

test: all
	@cc main.c -o test $(INC) $(LIB) $(DEBUGFLG)
	@echo "\n > \033[36mtest\033[m compilation [\033[32mDONE\033[m]\n"

.PHONY: all clean fclean re
