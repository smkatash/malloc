# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kanykei <kanykei@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/11 11:19:19 by kanykei           #+#    #+#              #
#    Updated: 2024/04/19 17:06:26 by kanykei          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ================================= Target =================================== #
NAME		:= libft.a

# ================================ Sources =================================== #

SRC			:= ft_memset.c ft_memcpy.c ft_putstr_fd.c ft_putchar_fd.c ft_itoa_base.c \
				ft_strlen.c ft_putnbr_fd.c

# ================================ Flags ===================================== #
OBJ			:= $(addprefix obj/,$(notdir $(SRC:.c=.o)))
CC			:= cc
CFLAGS 		:= -Wall -Wextra -Werror

# ================================ Rules ===================================== #

.SILENT:

all: $(NAME)

$(NAME)		: $(OBJ)
			ar rcs $(NAME) $(OBJ)

obj/%.o		: %.c | obj
			$(CC) $(CFLAGS) -c $< -o $@

obj			:
			mkdir obj

clean		:
			rm -rf obj
			@echo "deleting object files..."

fclean		: clean
			rm -rf $(NAME)

re: fclean all

.PHONY		:	all clean fclean re 