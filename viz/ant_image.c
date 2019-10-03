/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshellie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 16:17:07 by lshellie          #+#    #+#             */
/*   Updated: 2019/08/29 16:17:08 by lshellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vizualizer.h"
#include "../lem_in.h"

void		put_ant(t_mlx *mlx)
{
	int		i;
	t_room	*cur;
	t_pos	pos;
	void	*ant = make_ant(mlx);

	cur = mlx->map->rooms;
	i = -1;
	while (++i < mlx->map->num_of_rooms)
	{
		set_pos(&pos, mlx, &cur[i]);
		mlx_put_image_to_window(mlx->mlx, mlx->win, ant, pos.x0 - 5, pos.y0 - 7);
	}
}

void		put_ants(t_mlx *mlx)
{
	int		i;

	i = -1;
	mlx_clear_window(mlx->mlx, mlx->win);
	draw(mlx);
	while (++i < mlx->map->ants)
		mlx_put_image_to_window(mlx->mlx, mlx->win,\
		mlx->ant_img, (int)mlx->ants[i].x - 5, (int)mlx->ants[i].y - 7);
}

void		*make_ant(t_mlx *mlx)
{
	t_img		img;
	char 		*str;
	int 		color;
	int 		i;

	i = -1;
	str = ANT;
	color = set_colors(0, 255, 0, 0);
	if (!(img.img = mlx_new_image(mlx->mlx, 11, 16)))
		return (0);
	if (!(img.data = (int *)mlx_get_data_addr(img.img, &img.bpp, &img.size_line, &img.endian)))
		return (0);
	while (++i < 176)
	{
		if (str[i] == '1')
			img.data[i % 11 + (i / 11) * img.size_line / 4] = color;
	}
	return (img.img);
}
