/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshellie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 13:20:49 by lshellie          #+#    #+#             */
/*   Updated: 2019/08/25 13:20:50 by lshellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vizualizer.h"

static int		close_window(void *param)
{
	(void)param;
	exit(0);
}

void			hooks(t_mlx *mlx)
{
	mlx_loop_hook(mlx->mlx, make_step, mlx);
	mlx_hook(mlx->win, 17, 0, close_window, mlx->win);
	mlx_hook(mlx->win, 2, 0, key_event, mlx);
	mlx_loop(mlx->mlx);
}

void			init(t_mlx *mlx)
{
	if (!(mlx->mlx = mlx_init()))
		return ;
	if (!(mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "Lem_in")))
		return ;
	if (!(mlx->img = ft_memalloc(sizeof(t_img))))
		return ;
	if (!(mlx->img->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT)))
		return ;
	if (!(mlx->img->data = (int *)mlx_get_data_addr(mlx->img->img,
			&mlx->img->bpp, &mlx->img->size_line, &mlx->img->endian)))
		return ;
	calculate_positions(mlx);
	mlx->ant_img = make_ant(mlx);
	if (!(mlx->ants = (t_ant *)ft_memalloc(sizeof(t_ant) * mlx->map->ants)))
		return ;
	set_to_start(mlx);
	put_ants(mlx);
	hooks(mlx);
}
