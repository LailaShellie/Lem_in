/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solution_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshellie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 14:18:29 by lshellie          #+#    #+#             */
/*   Updated: 2019/10/03 14:18:30 by lshellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

int			find_start_end(t_map *map)
{
	t_room		*rooms;
	int 		i;

	i = -1;
	rooms = map->rooms;
	while (++i < map->num_of_rooms)
	{
		rooms[i].weight = -1;
		if (rooms[i].start)
			map->index_start = i;
		if (rooms[i].end)
			map->index_end = i;
	}
	return (1);
}

int			solution(t_map *map)
{
	int ret;
	int prev;
	int fl;

	fl = 0;
	prev = -1;
	find_start_end(map);
	map->step = 1;
	make_pipes(map);
	dijkstra(map);
	if (map->rooms[map->index_end].weight < 0)
		return (0);
	while (find_way(map))
	{
		find_sets(map);
		++map->step;
		if (prev < 0 || prev < map->sets->sum)
			prev = map->sets->sum;
		else if (prev == map->sets->sum)
			++fl;
	}
	clear_graph(map);
	dijkstra(map);
	while (fl < 50 && (ret = find_overlapping_ways(map)))
	{
		if (ret == 1)
		{
			find_sets(map);
			++map->step;
			if (prev < 0 || prev > map->sets->sum)
			{
				fl = 0;
				prev = map->sets->sum;
			}
			else if (prev == map->sets->sum)
				++fl;
		}
		else
		{
			clear_graph(map);
			dijkstra(map);
			++map->step;
		}
	}
	if (map->sets)
		print_solution(map->sets, map);
	return (1);
}
