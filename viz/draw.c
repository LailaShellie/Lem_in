/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshellie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 13:41:13 by lshellie          #+#    #+#             */
/*   Updated: 2019/08/25 13:41:14 by lshellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vizualizer.h"

int				set_colors(unsigned char o, unsigned char r, \
			unsigned char g, unsigned char b)
{
	int	i;
	int	tmp;
	int	res;
	int	j;

	i = 0;
	res = 0;
	tmp = 0;
	j = 0;
	while (i <= 31)
	{
		tmp = (i >= 0 && i <= 7) ? b : tmp;
		tmp = (i >= 8 && i <= 15) ? g : tmp;
		tmp = (i >= 16 && i <= 23) ? r : tmp;
		tmp = (i >= 24 && i <= 31) ? o : tmp;
		j = 0;
		while (j <= 7)
		{
			if (tmp & (1 << j))
				res |= 1 << i;
			++i;
			++j;
		}
	}
	return (res);
}

static void		plot(int x, int y, t_img *win, int color)
{
	int		*mas;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	mas = (int *)win->data;
	mas[x + y * win->size_line / 4] = color;
}

void			draw_room(t_room *room, t_mlx *mlx)
{
	t_pos	pos;
	int		j;

	set_pos(&pos, mlx, room);
	while (pos.x >= pos.y)
	{
		plot(pos.x0 - pos.y, pos.y0 + pos.x, mlx->img, room->color);
		plot(pos.x0 + pos.y, pos.y0 + pos.x, mlx->img, room->color);
		plot(pos.x0 - pos.x, pos.y0 + pos.y, mlx->img, room->color);
		plot(pos.x0 + pos.x, pos.y0 + pos.y, mlx->img, room->color);
		plot(pos.x0 - pos.y, pos.y0 - pos.x, mlx->img, room->color);
		plot(pos.x0 + pos.y, pos.y0 - pos.x, mlx->img, room->color);
		plot(pos.x0 - pos.x, pos.y0 - pos.y, mlx->img, room->color);
		plot(pos.x0 + pos.x, pos.y0 - pos.y, mlx->img, room->color);
		if (pos.err <= 0)
			pos.err += 2 * ++pos.y + 1;
		if (pos.err > 0)
			pos.err -= 2 * --pos.x + 1;
	}
	j = -1;
	while (++j < room->num_of_links)
		draw_line(mlx, room, &mlx->map->rooms[room->links[j]]);
}

void			put_names(t_mlx *mlx)
{
	t_pos	pos;
	int		i;

	i = -1;
	while (++i < mlx->map->num_of_rooms)
	{
		set_pos(&pos, mlx, &mlx->map->rooms[i]);
		mlx_string_put(mlx->mlx, mlx->win, pos.x0 + pos.x,
				pos.y0 + pos.y, set_colors(0, 255, 255, 255),
				mlx->map->rooms[i].name);
	}
}

void			draw(t_mlx *mlx)
{
	t_room	*cur;
	int		num;
	int		i;
	int		j;

	i = -1;
	bzero(mlx->img->data, WIDTH * HEIGHT * 4);
	num = mlx->map->num_of_rooms;
	cur = mlx->map->rooms;
	while (++i < num)
	{
		j = -1;
		if (cur[i].start)
			cur[i].color = set_colors(0, 0, 255, 0);
		else if (cur[i].end)
			cur[i].color = set_colors(0, 255, 255, 0);
		else
			cur[i].color = set_colors(0, 255, 0, 0);
		draw_room(&cur[i], mlx);
		cur[i].visited = 1;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img->img, 0, 0);
	put_names(mlx);
}
