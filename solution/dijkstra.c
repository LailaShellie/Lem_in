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

int 		is_blocked(t_map *map, int cur, int next)
{
	return (map->pipes[cur + next * map->num_of_rooms] == -1
	&& map->pipes[next + cur * map->num_of_rooms] == -1);
}

t_queue		*new_queue(t_map *map, int i)
{
	t_queue		*new;

	if (!(new = (t_queue *)ft_memalloc(sizeof(t_queue))))
		return (0);
	new->weight = map->rooms[i].weight;
	new->i = i;
	new->next = 0;
	return (new);
}

int 		get_from_queue(t_map *map)
{
	t_queue *tmp;
	int ret;

	if (!map->queue)
		return (-1);
	tmp = map->queue;
	ret = tmp->i;
	map->queue = tmp->next;
	free(tmp);
	return (ret == map->index_end ? -1 : ret);
}

//int 		get_from_queue(t_map *map)
//{
//	t_queue		*tmp;
//	int 		ret;
//
//	if (!map->queue)
//		return (-1);
//	tmp = map->queue;
//	ret = tmp->i;
//	if (tmp->next)
//		map->queue = tmp->next;
//	else
//		map->queue = 0;
//	free(tmp);
//	return (ret == map->index_end ? -1 : ret);
//}

int 		put_to_queue(t_map *map, int i)
{
	t_queue		*cur;
	t_queue		*prev;
	t_queue		*new;

	new = new_queue(map, i);
	if (!(map->queue))
		map->queue = new;
	else
	{
		cur = map->queue;
		prev = 0;
		while (cur)
		{
			if (cur->weight > new->weight)
				break ;
			prev = cur;
			cur = cur->next;
		}
		if (!prev)
			map->queue = new;
		else
			prev->next = new;
		new->next = cur;
	}
	return (1);
}

void		clear_graph(t_map *map)
{
	int 	i;
	int 	cur;
	t_room	*room;

	cur = -1;
	i = -1;
	room = map->rooms;
	while (++cur < map->num_of_rooms)
	{
		while (++i < room[cur].num_of_links)
		{
			if (!is_blocked(map, cur, room[cur].links[i]))
			{
				map->pipes[cur + room[cur].links[i] * map->num_of_rooms] = 0;
				map->pipes[room[cur].links[i] + cur * map->num_of_rooms] = 0;
			}
			room[cur].sh = 0;
			room[cur].weight = -1;
		}
		i = -1;
	}
}

int			dijkstra(t_map *map)
{
	int 	cur;
	int 	i;
	int 	k;
	t_room	*room;

	k = -1;
	room = map->rooms;
	cur = map->index_start;
	room[cur].weight = 0;
	while (++k < map->num_of_rooms)
	{
		i = -1;
		while (cur >= 0 && ++i < room[cur].num_of_links)
		{
			if (is_blocked(map, cur, room[cur].links[i]))
				continue ;
			if ((room[room[cur].links[i]].weight == -1 || room[cur].weight + 1 < room[room[cur].links[i]].weight))
			{
				room[room[cur].links[i]].weight = room[cur].weight + 1;
				put_to_queue(map, room[cur].links[i]);
			}
		}
		cur = get_from_queue(map);
	}
	return (0);
}
