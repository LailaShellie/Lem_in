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

SRC_VAL = read_and_save.c validation.c find.c define.c check_parts.c \
	free.c make_map.c make_links.c
OBJ_VAL = $(SRC_VAL:.c=.o)

SRC_LEM = main.c

OBJ_LEM = $(SRC_LEM:.c=.o)

SRC_VIZ = vizualizer_main.c init.c draw.c positions.c wu.c bresenham.c draw_line.c keyboard.c

OBJ_VIZ = $(SRC_VIZ:.c=.o)

LIB = libft/libft.a

LEM = lem_in

VIZ = vizualizer

all: $(LEM) $(VIZ)

$(VIZ): $(OBJ_VIZ)
	gcc -Wall -Wextra -Werror -L. $(LIB) -o $(VIZ) $(OBJ_VIZ) $(OBJ_VAL) -L mlx -l mlx -framework OpenGL -framework AppKit

$(LEM): $(OBJ_LEM) $(OBJ_VAL) $(LIB)
	gcc -Wall -Wextra -Werror -L. $(LIB) -o $(LEM) $(OBJ_LEM) $(OBJ_VAL)
$(LIB):
	make -C ./libft
$(OBJ_VAL):
	gcc -c -I. lem_in.h $(addprefix validation/, $(SRC_VAL))
$(OBJ_LEM):
	gcc -c -I. lem_in.h $(SRC_LEM)
$(OBJ_VIZ):
	gcc -c -I. viz/vizualizer.h $(addprefix viz/, $(SRC_VIZ))
clean:
	make clean -C ./libft
	rm -rf $(OBJ_LEM) $(OBJ_VIZ) $(OBJ_VAL)
fclean: clean
	make fclean -C ./libft
	rm -rf $(LEM) $(VIZ)
re: fclean all