/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshellie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 13:21:05 by lshellie          #+#    #+#             */
/*   Updated: 2019/08/26 13:21:07 by lshellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vizualizer.h"

int				zoom(int key_code, t_mlx *win)
{
	if (key_code == 78)
	{
		if (win->img->zoom != 1)
			win->img->zoom -= 1;
	}
	else if (key_code == 69)
		win->img->zoom += 1;
	printf("%d\n", win->img->zoom);
	return (0);
}

int 			move(int key_code, t_mlx *win)
{
	if (key_code == 123)
		win->img->dx += 10;
	else if (key_code == 124)
		win->img->dx -= 10;
	if (key_code == 125)
		win->img->dy -= 10;
	else if (key_code == 126)
		win->img->dy += 10;
	return (0);
}

int				key_event(int key_code, t_mlx *win)
{
	if (key_code == 53)
		exit(0);
	else if (key_code >= 123 && key_code <= 126)
		move(key_code, win);
	else if (key_code == 69 || key_code == 78)
		zoom(key_code, win);
	mlx_clear_window(win->mlx, win->win);
	draw(win);
	return (0);
}