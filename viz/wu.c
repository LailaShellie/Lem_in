/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wu.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshellie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 18:06:28 by lshellie          #+#    #+#             */
/*   Updated: 2019/08/21 18:06:29 by lshellie         ###   ########.fr       */
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
	if (mas[x + y * win->size_line / 4] == 0)
		mas[x + y * win->size_line / 4] = color;
}

void			wu_low(t_mlx *mlx, t_line *l0, t_line *l1)
{
	float	grad;
	float	y;

	if (l1->x - l0->x)
		grad = (float)(l1->y - l0->y) / (float)(l1->x - l0->x);
	else
		grad = 0;
	plot(l0->x, l0->y, 0, mlx->img);
	plot(l1->x, l1->y, 0, mlx->img);
	y = l0->y + grad;
	while (++l0->x < l1->x)
	{
		plot(l0->x, (int)y, (y - floor(y)), mlx->img);
		plot(l0->x, (int)(y) + 1, 1 - (y - floor(y)), mlx->img);
		y += grad;
	}
}

void			wu_hight(t_mlx *mlx, t_line *l0, t_line *l1)
{
	float	grad;
	float	x;

	if (l1->x - l0->x)
		grad = (float)(l1->x - l0->x) / (float)(l1->y - l0->y);
	else
		grad = 0;
	plot(l0->x, l0->y, 0, mlx->img);
	plot(l1->x, l1->y, 0, mlx->img);
	x = l0->x + grad;
	while (++l0->y < l1->y)
	{
		plot(x, (int)l0->y, (x - floor(x)), mlx->img);
		plot(x + 1, (int)(l0->y), 1 - (x - floor(x)), mlx->img);
		x += grad;
	}
}
