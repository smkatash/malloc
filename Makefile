# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kanykei <kanykei@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/11 11:19:19 by kanykei           #+#    #+#              #
#    Updated: 2024/04/19 17:08:06 by kanykei          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

# ================================= Target =================================== #
NAME		:= libft_malloc_$(HOSTTYPE).so
LIB_NAME 	:= libft_malloc.so

# ================================ Sources =================================== #

VPATH		:= srcs

SRC			:= malloc.c alloc.c page.c show.c free.c realloc.c block.c align.c shift.c

# ================================ Flags ===================================== #
OBJ			:= $(addprefix obj/,$(notdir $(SRC:.c=.o)))
CC			:= gcc
CFLAGS 		:= -Wall -Wextra -Werror

# ============================== Libraries ==================================== #
INCFL		:=	-I./include -I./libs/libft
LIBS		:= 	-L./libs/libft -lft
LIBFT		:=	libs/libft/libft.a

# ================================ Rules ===================================== #
.SILENT:

all: $(LIB_NAME)

$(NAME)		: $(OBJ) $(LIBFT) 
			$(CC) $(CFLAGS) -shared -o $(NAME) $(OBJ) $(LIBS)
			@echo "\033[1;32m malloc is compiled \033[0m"

$(LIB_NAME)	: $(NAME)
			ln -sf $(NAME) $(LIB_NAME)

obj/%.o		: %.c | obj
			$(CC) $(CFLAGS) $(INCFL) -c $< -o $@

obj			:
			mkdir obj

$(LIBFT):
			- (cd libs/libft && make && make clean)

clean		:
			rm -rf obj
			@echo "deleting object files..."

fclean		: clean
			rm $(NAME) $(LIB_NAME)
			@echo "deleting malloc..."
			- (cd libs/libft && make fclean)

re			: fclean all

test		:
			gcc main.c -o main $(NAME)
			./main

.PHONY		:	all clean fclean re 

