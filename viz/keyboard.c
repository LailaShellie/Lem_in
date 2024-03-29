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

void			set_to_null(t_mlx *mlx)
{
	int		i;

	i = -1;
	while (++i < mlx->map->ants)
	{
		mlx->ants[i].dx = 0;
		mlx->ants[i].dy = 0;
	}
}

int				key_event(int key_code, t_mlx *win)
{
	if (key_code == 53)
		exit(0);
	else if (key_code == 49)
		sleep(1);
	return (0);
}
