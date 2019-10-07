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

t_lst	*choose_set(t_lst *lst)
{
	t_lst		*cur;
	t_lst		*tmp;

	tmp = lst;
	cur = lst;
	while (cur)
	{
		if ((cur->sum < tmp->sum && !cur->bad) || tmp->bad)
			tmp = cur;
		cur = cur->next;
	}
	return (tmp);
}

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

int 		show_end_weight(t_map *map)
{
	int		i;

	i = -1;
	printf("End %d\n", map->rooms[map->index_end].weight);
	while (++i < map->rooms[map->index_end].num_of_links)
	{
		printf("%s %d\n", map->rooms[map->rooms[map->index_end].links[i]].name, map->rooms[map->rooms[map->index_end].links[i]].weight);
	}
	return (0);
}

int			solution(t_map *map)
{
	int 	ret;

	find_start_end(map);
	map->step = 1;
	make_pipes(map);
//	show_map(map);
	dijkstra(map);
//	show_end_weight(map);
//	show_map(map);
	if (map->rooms[map->index_end].weight < 0)
		return (0);
//	remove_dead_pipes(map);
	while ((ret = find_way(map)))
	{
		find_sets(map);
		++map->step;
//		if (ret == 1)
//			update_dijkstra(map);
	}
//	ft_show_sets(map);
//	show_pipes(map);
	if (map->sets)
		print_solution(choose_set(map->sets), map);
	return (1);
}
