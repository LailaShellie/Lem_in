/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_overlapping_ways.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshellie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 17:01:38 by lshellie          #+#    #+#             */
/*   Updated: 2019/10/08 17:01:39 by lshellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

void	block_pipe(t_map *map, int cur, int next, int fl)
{
	if (fl)
	{
		map->pipes[cur + next * map->num_of_rooms] = -1;
		map->pipes[next + cur * map->num_of_rooms] = -1;
	}
	else
	{
		map->pipes[cur + next * map->num_of_rooms] = 0;
		map->pipes[next + cur * map->num_of_rooms] = 0;
	}
}

int		break_way(t_map *map, int cur)
{
	int		i;
	t_room	*room;
	int		fl;

	fl = 1;
	i = -1;
	room = map->rooms;
	while (++i < room[cur].num_of_links)
	{
		if ((room[cur].sh == room[room[cur].links[i]].sh
		&& room[cur].weight < room[room[cur].links[i]].weight)
		|| room[cur].links[i] == map->index_end)
		{
			block_pipe(map, cur, room[cur].links[i], fl);
			if (room[room[cur].links[i]].num_of_links > 2)
				fl = 0;
			cur = room[cur].links[i];
			i = -1;
		}
		if (cur == map->index_end)
			return (-1);
	}
	return (-1);
}

int		find_overlapping_ways(t_map *map, t_room *room)
{
	int		cur;
	int		i;

	i = -1;
	if ((cur = find_min_weight(map, map->index_end)) < 0)
		return (0);
	map->pipes[cur + map->index_end * map->num_of_rooms] = -1;
	while (++i < room[cur].num_of_links)
	{
		if (cur == map->index_start)
			return (1);
		if (room[room[cur].links[i]].weight >= 0
		&& room[cur].weight > room[room[cur].links[i]].weight
			&& map->pipes[cur + room[cur].links[i] * map->num_of_rooms] == 0)
		{
			if (room[room[cur].links[i]].sh
			&& room[room[cur].links[i]].sh != map->step)
				return (break_way(map, room[cur].links[i]));
			room[cur].sh = map->step;
			map->pipes[room[cur].links[i] + cur * map->num_of_rooms] = -1;
			cur = room[cur].links[i];
			i = -1;
		}
	}
	return (1);
}
