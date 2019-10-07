/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_dijkstra.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshellie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 17:52:32 by lshellie          #+#    #+#             */
/*   Updated: 2019/10/06 17:52:33 by lshellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

int 		clear_graph(t_map *map)
{
	int 	cur;
	int 	i;
	t_room	*room;

	room = map->rooms;
	cur = -1;
	while (++cur < map->num_of_rooms)
	{
		i = -1;
		while (++i < room[cur].num_of_links)
		{
			if (map->pipes[cur + room[cur].links[i] * map->num_of_rooms].status == -1
			&& map->pipes[room[cur].links[i] + cur * map->num_of_rooms].status == -1)
				continue ;
			map->pipes[cur + room[cur].links[i] * map->num_of_rooms].status = 0;
			map->pipes[room[cur].links[i] + cur * map->num_of_rooms].status = 0;
		}
		room[cur].sh = 0;
		room[cur].weight = -1;
		room[cur].visited = 0;
	}
	return (1);
}

int 		update_dijkstra(t_map *map)
{
	int 	i;
	int 	j;
	int 	k;
	t_room	*rooms;

	clear_graph(map);
	rooms = map->rooms;
	i = map->index_start;
	rooms[i].weight = 0;
	k = -1;
	while (++k < map->num_of_rooms)
	{
		j = -1;
		while (++j < rooms[i].num_of_links)
		{
			if (map->pipes[i + rooms[i].links[j] * map->num_of_rooms].status == -1
			&& map->pipes[rooms[i].links[j] + i * map->num_of_rooms].status == -1)
				continue ;
			if (i != map->index_end && (rooms[rooms[i].links[j]].weight < 0
			|| rooms[rooms[i].links[j]].weight > rooms[i].weight + 1))
				rooms[rooms[i].links[j]].weight = rooms[i].weight + 1;
		}
		rooms[i].visited = 1;
//		if ((i = find_next(map)) < 0)
//			break ;
	}
	return (0);
}
