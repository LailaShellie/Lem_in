/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshellie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 18:16:42 by lshellie          #+#    #+#             */
/*   Updated: 2019/10/03 18:16:43 by lshellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

int			show_pipes(t_map *map)
{
	int 	i;
	int 	j;

	i = -1;
	while (++i < map->num_of_rooms)
	{
		j = -1;
		while (++j < map->num_of_rooms)
		{
			printf("%2d ", map->pipes[j + i * map->num_of_rooms].status);
		}
		printf("\n");
	}
	return (1);
}

int			check_this_way(t_map *map, int cur)
{
	int 	i;
	t_room	*rooms;

	rooms = map->rooms;
	i = -1;
	while (++i < rooms[cur].num_of_links)
	{
		if (rooms[cur].links[i] == map->index_start)
		{
			map->pipes[rooms[cur].links[i] + cur * map->num_of_rooms].good = 1;
			map->pipes[cur + rooms[cur].links[i] * map->num_of_rooms].good = 1;
			return (0);
		}
		if (rooms[rooms[cur].links[i]].weight + 1 == rooms[cur].weight)
		{
			cur = rooms[cur].links[i];
			i = -1;
			continue ;
		}
	}
	return (1);
}

int			remove_dead_pipes(t_map *map)
{
	int 	i;
	int 	j;
	int 	k;
	t_room	*rooms;

	i = -1;
	rooms = map->rooms;
	while (++i < rooms[map->index_end].num_of_links)
		check_this_way(map, rooms[map->index_end].links[i]);
	return (0);
}

int			make_pipes(t_map *map)
{
	t_pipe		*pipes;

	if (!(pipes = (t_pipe *)ft_memalloc(sizeof(t_pipe) * map->num_of_rooms * map->num_of_rooms)))
		return (0);
	map->pipes = pipes;
	return (1);
}