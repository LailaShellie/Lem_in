/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshellie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 12:18:11 by lshellie          #+#    #+#             */
/*   Updated: 2019/08/30 12:18:12 by lshellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vizualizer.h"

void		set_dx_dy(t_mlx *mlx, int ant, int room)
{
	t_pos		pos;

	if (room >= 0)
	{
		set_pos(&pos, mlx, &mlx->map->rooms[room]);
		mlx->ants[ant].dx = (pos.x0 - mlx->ants[ant].x) / 100;
		mlx->ants[ant].dy = (pos.y0 - mlx->ants[ant].y) / 100;
	}
	else
	{
		mlx->ants[ant].dx = 0;
		mlx->ants[ant].dy = 0;
	}
}

void		do_step(t_mlx *mlx)
{
	int		j;

	j = -1;
	while (++j < mlx->map->ants)
	{
		mlx->ants[j].x += mlx->ants[j].dx;
		mlx->ants[j].y += mlx->ants[j].dy;
	}
}

void		exec_turn(char *str, t_mlx *mlx)
{
	char	**turn;
	char	**ant_n_room;
	int		i;
	int		ant;
	int		room;

	i = -1;
	turn = ft_strsplit(str, ' ');
	while (turn[++i])
	{
		ant_n_room = ft_strsplit(turn[i], '-');
		ant = ft_atoi(&ant_n_room[0][1]) - 1;
		room = find_index_by_name(mlx->map->rooms, \
		mlx->map->num_of_rooms, ant_n_room[1]);
		set_dx_dy(mlx, ant, room);
		ft_free_split(ant_n_room, 2);
	}
	ft_free_split(turn, i);
}

void		set_to_start(t_mlx *mlx)
{
	int		start;
	int		i;
	t_pos	pos;

	i = -1;
	start = find_start(mlx->map);
	set_pos(&pos, mlx, &(mlx->map->rooms[start]));
	while (++i < mlx->map->ants)
	{
		mlx->ants[i].x = pos.x0;
		mlx->ants[i].y = pos.y0;
		mlx->ants[i].dx = 0;
		mlx->ants[i].dy = 0;
	}
}

int			make_step(t_mlx *mlx)
{
	int		i;

	i = -1;
	if (mlx->step == 100 || mlx->turn == 0)
	{
		if (!mlx->turns[mlx->turn])
			return (0);
		set_to_null(mlx);
		exec_turn(mlx->turns[mlx->turn], mlx);
		++mlx->turn;
		mlx->step = 0;
	}
	else if (mlx->step < 100)
	{
		do_step(mlx);
		put_ants(mlx);
		++mlx->step;
	}
	return (0);
}
