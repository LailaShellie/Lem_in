# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lshellie <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/23 16:35:44 by lshellie          #+#    #+#              #
#    Updated: 2019/09/30 14:26:36 by ubartemi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_VAL = read_and_save.c validation.c find.c define.c check_parts.c \
          	free.c make_map.c make_links.c

OBJ_VAL = $(SRC_VAL:.c=.o)

SRC_SOL = solution_main.c sets.c sets_basic.c calculate_turns.c print_solution.c dijkstra.c pipes.c find_way.c find_overlapping_ways.c

OBJ_SOL = $(SRC_SOL:.c=.o)

SRC_LEM = main.c

OBJ_LEM = $(SRC_LEM:.c=.o)

SRC_VIZ = vizualizer_main.c init.c draw.c positions.c wu.c draw_line.c \
 keyboard.c ant_image.c move.c

OBJ_VIZ = $(SRC_VIZ:.c=.o)

LIB = libft/libft.a

MLX = mlx

LEM = lem-in

VIZ = vizualizer

all: $(LEM) $(VIZ)

$(VIZ): $(OBJ_VIZ) $(MLX)
	gcc -Wall -Wextra -Werror $(LIB) -o $(VIZ) $(OBJ_VIZ) $(OBJ_VAL) -L ./mlx -lmlx -framework OpenGL -framework AppKit

$(LEM): $(OBJ_LEM) $(OBJ_VAL) $(LIB) $(OBJ_SOL)
	gcc -Wall -Wextra -Werror $(LIB) -o $(LEM) $(OBJ_LEM) $(OBJ_VAL) $(OBJ_SOL)
$(LIB):
	make -C ./libft
$(MLX):
	make -C ./mlx
$(OBJ_VAL):
	gcc -c -I lem_in.h $(addprefix validation/, $(SRC_VAL))
$(OBJ_LEM):
	gcc -c -I lem_in.h $(SRC_LEM)
$(OBJ_SOL):
	gcc -c -I lem_in.h $(addprefix solution/, $(SRC_SOL))
$(OBJ_VIZ):
	gcc -c -I viz/vizualizer.h $(addprefix viz/, $(SRC_VIZ))
clean:
	make clean -C ./libft
	rm -rf $(OBJ_LEM) $(OBJ_VIZ) $(OBJ_VAL) $(OBJ_SOL)
fclean: clean
	make fclean -C ./libft
	rm -rf $(LEM) $(VIZ)
re: fclean all
