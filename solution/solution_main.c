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

int			is_blocked(t_map *map, int cur, int next)
{
	return (map->pipes[cur + next * map->num_of_rooms] == -1
			&& map->pipes[next + cur * map->num_of_rooms] == -1);
}

int			make_pipes(t_map *map)
{
	int		*pipes;

	if (!(pipes = (int *)ft_memalloc(sizeof(int)
			* (map->num_of_rooms * map->num_of_rooms))))
		return (0);
	map->pipes = pipes;
	return (1);
}

int			find_start_end(t_map *map)
{
	t_room		*rooms;
	int			i;

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

void		solution2(t_map *map)
{
	int ret;
	int prev;
	int fl;

	fl = 0;
	prev = -1;
	while (fl < 50 && (ret = find_overlapping_ways(map, map->rooms)))
	{
		if (ret == 1)
		{
			find_sets(map);
			++map->step;
			if (map->sets && (prev < 0 || prev < map->sets->sum))
			{
				fl = 0;
				prev = map->sets->sum;
			}
			else if (map->sets && prev == map->sets->sum)
				++fl;
		}
		else
			clear_graph(map);
	}
}

int			solution(t_map *map)
{
	int prev;
	int fl;

	fl = 0;
	prev = -1;
	map->step = 1;
	find_start_end(map);
	make_pipes(map);
	clear_graph(map);
	if (map->rooms[map->index_end].weight < 0)
		return (0);
	while (find_way(map))
	{
		find_sets(map);
		++map->step;
		if (map->sets && (prev < 0 || prev < map->sets->sum))
			prev = map->sets->sum;
		else if (map->sets && prev == map->sets->sum)
			++fl;
	}
	clear_graph(map);
	solution2(map);
	if (map->sets)
		print_solution(map->sets, map);
	return (1);
}
