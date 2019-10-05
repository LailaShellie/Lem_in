/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dijkstra.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshellie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 15:14:00 by lshellie          #+#    #+#             */
/*   Updated: 2019/10/03 15:14:01 by lshellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

int			find_min(t_map	*map, int cur)
{
	int 	i;
	int 	ret;
	t_room	*rooms;

	rooms = map->rooms;
	i = 0;
	ret = -1;
	while (i < rooms[cur].num_of_links)
	{
		if ((ret == -1 || rooms[ret].weight >= rooms[rooms[cur].links[i]].weight)
		&& map->pipes[rooms[cur].links[i] + cur * map->num_of_rooms].status == 0)
			ret = rooms[cur].links[i];
		++i;
	}
	return (ret);
}

int			find_way(t_map *map)
{
	int 	cur;
	int 	i;
	t_room	*room;

	i = -1;
	room = map->rooms;
	if ((cur = find_min(map, map->index_end)) < 0)
		return (0);
	map->pipes[cur + map->index_end * map->num_of_rooms].status = -1;
	while (++i < room[cur].num_of_links)
	{
		if (room[cur].weight - 1 == room[room[cur].links[i]].weight)
		{
			room[cur].sh = map->step;
			map->pipes[cur + room[cur].links[i] * map->num_of_rooms].status = -1;
			cur = room[cur].links[i];
			i = -1;
		}
	}
	return (1);
}

int			find_next(t_map *map)
{
	int 	i;
	t_room	*rooms;

	rooms = map->rooms;
	i = -1;
	while (++i < map->num_of_rooms)
	{
		if (!rooms[i].visited && rooms[i].weight > 0)
			return (i);
	}
	return (-1);
}

int			dijkstra(t_map *map)
{
	int 	i;
	int 	j;
	int 	k;
	t_room	*rooms;

	rooms = map->rooms;
	i = map->index_start;
	rooms[i].weight = 0;
	k = -1;
	while (++k < map->num_of_rooms)
	{
		j = -1;
		while (++j < rooms[i].num_of_links)
		{
			if (rooms[rooms[i].links[j]].weight < 0
			        || rooms[rooms[i].links[j]].weight > rooms[i].weight + 1)
				rooms[rooms[i].links[j]].weight = rooms[i].weight + 1;
		}
		rooms[i].visited = 1;
		if ((i = find_next(map)) < 0)
			break ;
	}
	return (0);
}
