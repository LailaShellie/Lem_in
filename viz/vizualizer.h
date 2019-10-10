/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vizualizer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshellie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 12:57:31 by lshellie          #+#    #+#             */
/*   Updated: 2019/08/25 12:57:34 by lshellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIZUALIZER_H
# define VIZUALIZER_H
# include "../lem_in.h"
# include "mlx.h"
# include <math.h>
# define WIDTH 1000
# define HEIGHT 1000

typedef struct		s_ant
{
	float			x;
	float			y;
	float			dx;
	float			dy;
}					t_ant;

typedef struct		s_img
{
	void			*img;
	int				bpp;
	int				size_line;
	int				endian;
	int				*data;
	int				dx;
	int				dy;
	int				zoom;
	int				width;
	int				height;
}					t_img;

typedef struct		s_mlx
{
	void			*mlx;
	void			*win;
	t_img			*img;
	t_map			*map;
	t_ant			*ants;
	void			*ant_img;
	char			**turns;
	int				turn;
	int				num_of_turns;
	int				step;
}					t_mlx;

typedef struct		s_max_min
{
	int				min_x;
	int				max_x;
	int				max_y;
	int				min_y;
	int				i;
}					t_max_min;

typedef struct		s_line
{
	int				x;
	int				y;
}					t_line;

typedef struct		s_pos
{
	int				x0;
	int				y0;
	int				x;
	int				y;
	int				err;
}					t_pos;

void				set_to_null(t_mlx *mlx);
void				init(t_mlx *mlx);
void				draw(t_mlx *mlx);
void				calculate_positions(t_mlx *mlx);
void				set_pos(t_pos *pos, t_mlx *mlx, t_room *room);
void				wu_hight(t_mlx *mlx, t_line *l0, t_line *l1);
void				wu_low(t_mlx *mlx, t_line *l0, t_line *l1);
void				draw_line(t_mlx *mlx, t_room *room0, t_room *room1);
int					set_colors(unsigned char o, unsigned char r, \
			unsigned char g, unsigned char b);
int					key_event(int key_code, t_mlx *win);
void				*make_ant(t_mlx *mlx);
void				put_ant(t_mlx *mlx);
int					move_ants(t_mlx *mlx);
void				set_to_start(t_mlx *mlx);
void				put_ants(t_mlx *mlx);
int					make_step(t_mlx *mlx);
int					find_start(t_map *nest);

#endif
