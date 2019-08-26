/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshellie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 18:04:59 by lshellie          #+#    #+#             */
/*   Updated: 2019/08/21 18:05:01 by lshellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vizualizer.h"

static void		plot(int x, int y, float o, t_img *win)
{
	int		*mas;
	int		color;

	color = set_colors(255 * o, 255, 255, 255);
	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	mas = (int *)win->data;
	mas[x + y * win->size_line / 4] = color;
}

void			bresenham_hight(t_mlx *mlx, t_line *l0, t_line *l1)
{
	int dx;
	int dy;
	int xi;
	int d;

	dx = l1->x - l0->x;
	dy = l1->y - l0->y;
	xi = 1;
	if (dx < 0)
	{
		xi = -1;
		dx = -dx;
	}
	d = 2 * dx - dy;
	while (l0->y < l1->y)
	{
		plot(l0->x, l0->y, 0, mlx->img);
		if (d > 0)
		{
			l0->x += xi;
			d = d - 2 * dy;
		}
		d = d + 2 * dx;
		++l0->y;
	}
}

void			bresenham_low(t_mlx *mlx, t_line *l0, t_line *l1)
{
	int dx;
	int dy;
	int yi;
	int d;

	dx = l1->x - l0->x;
	dy = l1->y - l0->y;
	yi = 1;
	if (dy < 0)
	{
		yi = -1;
		dy = -dy;
	}
	d = 2 * dy - dx;
	while (l0->x < l1->x)
	{
		plot(l0->x, l0->y, 0, mlx->img);
		if (d > 0)
		{
			l0->y += yi;
			d = d - 2 * dx;
		}
		d = d + 2 * dy;
		++l0->x;
	}
}
