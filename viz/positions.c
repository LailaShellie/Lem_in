/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   positions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshellie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 15:41:27 by lshellie          #+#    #+#             */
/*   Updated: 2019/08/25 15:41:28 by lshellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vizualizer.h"

void		set_pos(t_pos *pos, t_mlx *mlx, t_room *room)
{
	pos->x0 = (room->x - mlx->img->width / 2)
			* mlx->img->zoom + WIDTH / 2 + mlx->img->dx;
	pos->y0 = (room->y - mlx->img->height / 2)
			* mlx->img->zoom + HEIGHT / 2 + mlx->img->dy;
	pos->x = 20;
	pos->y = 0;
	pos->err = 0;
}

static void	set_center(t_mlx *mlx, t_max_min *i)
{
	mlx->img->width = ft_abs(i->max_x - i->min_x);
	mlx->img->height = ft_abs(i->max_y - i->min_y);
	mlx->img->zoom = WIDTH;
	mlx->img->zoom /= mlx->img->width
			> mlx->img->height ? mlx->img->width : mlx->img->height;
	mlx->img->zoom -= mlx->img->zoom / 4;
}

void		calculate_positions(t_mlx *mlx)
{
	t_max_min i;

	i.i = -1;
	while (++i.i < mlx->map->num_of_rooms)
	{
		if (i.i == 0)
		{
			i.max_x = mlx->map->rooms[i.i].x;
			i.max_x = mlx->map->rooms[i.i].x;
			i.max_y = mlx->map->rooms[i.i].y;
			i.max_y = mlx->map->rooms[i.i].y;
		}
		else
		{
			if (i.max_x < mlx->map->rooms[i.i].x)
				i.max_x = mlx->map->rooms[i.i].x;
			if (i.max_y < mlx->map->rooms[i.i].y)
				i.max_y = mlx->map->rooms[i.i].y;
			if (i.min_x > mlx->map->rooms[i.i].x)
				i.min_x = mlx->map->rooms[i.i].x;
			if (i.min_y > mlx->map->rooms[i.i].y)
				i.min_y = mlx->map->rooms[i.i].y;
		}
	}
	set_center(mlx, &i);
}
