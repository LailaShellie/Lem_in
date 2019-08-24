# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lshellie <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/23 16:35:44 by lshellie          #+#    #+#              #
#    Updated: 2019/08/23 16:35:46 by lshellie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c read_and_save.c validation.c find.c define.c check_parts.c \
	free.c make_map.c make_links.c

HDR = lem_in.h

OBJ = $(SRC:.c=.o)

LIB = libft/libft.a

NAME = lem_in

all: $(NAME)

$(NAME): $(OBJ) $(LIB)
	gcc -Wall -Wextra -Werror -L. $(LIB) -o $(NAME) $(OBJ)
$(LIB):
	make -C ./libft
%.o: %.c
	gcc -I $(HDR) -c $<
clean:
	make clean -C ./libft
	rm -rf $(OBJ)
fclean: clean
	make fclean -C ./libft
	rm -rf $(NAME)
re: fclean all