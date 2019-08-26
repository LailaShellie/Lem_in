/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshellie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 12:36:53 by lshellie          #+#    #+#             */
/*   Updated: 2019/08/13 12:36:54 by lshellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vizualizer.h"

static void	add_position(t_mlx *mlx, t_line *l0, t_line *l1)
{
	l0->x = (l0->x - mlx->img->width / 2) * mlx->img->zoom + WIDTH / 2 + mlx->img->dx;
	l0->y = (l0->y - mlx->img->height / 2) * mlx->img->zoom + HEIGHT / 2 + mlx->img->dy;
	l1->x = (l1->x - mlx->img->width / 2) * mlx->img->zoom + WIDTH / 2 + mlx->img->dx;
	l1->y = (l1->y - mlx->img->height / 2) * mlx->img->zoom + HEIGHT / 2 + mlx->img->dy;
}

static void	init_line(t_line *l0, t_line *l1, t_room *room0, t_room *room1)
{
	l0->x = room0->x;
	l0->y = room0->y;
	l1->x = room1->x;
	l1->y = room1->y;
}

void	draw_line(t_mlx *mlx, t_room *room0, t_room *room1)
{
	t_line l0;
	t_line l1;

	init_line(&l0, &l1, room0, room1);
	add_position(mlx, &l0, &l1);
	if ((l0.x >= WIDTH && l1.x >= WIDTH) || (l0.y >= HEIGHT && l1.y >= HEIGHT))
		return;
	if ((l0.x < 0 && l1.x < 0) || (l0.y < 0 && l1.y < 0))
		return;
	if (abs(l1.y - l0.y) < abs(l1.x - l0.x))
	{
		if (l0.x > l1.x)
			wu_low(mlx, &l1, &l0);
			//bresenham_low(mlx, &l1, &l0);
		else
			wu_low(mlx, &l0, &l1);
			//bresenham_low(mlx, &l0, &l1);
	}
	else
	{
		if (l0.y > l1.y)
			wu_hight(mlx, &l1, &l0);
			//bresenham_hight(mlx, &l1, &l0);
		else
			wu_hight(mlx, &l0, &l1);
			//bresenham_hight(mlx, &l0, &l1);
	}
}
