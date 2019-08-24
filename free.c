/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshellie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 15:14:01 by lshellie          #+#    #+#             */
/*   Updated: 2019/08/24 15:14:02 by lshellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		free_rooms(t_room **rooms, int num)
{
	int		i;
	t_room	*room;

	if (!rooms || !*rooms)
		return ;
	room = *rooms;
	i = 0;
	while (i < num)
	{
		if ((room[i]).name)
			free((room[i]).name);
		if ((room[i]).links)
			free((room[i]).links);
		++i;
	}
	free(*rooms);
	*rooms = 0;
}

void			show_map(t_map *map)
{
	int 	i;
	int 	j;

	i = -1;
	printf("%d - ants\n%d - num_of_rooms\n", map->ants, map->num_of_rooms);
	while (++i < map->num_of_rooms)
	{
		printf("----------------\n");
		printf("%s - name\n(%d : %d)\n", map->rooms[i].name, map->rooms[i].x, map->rooms[i].y);
		if (map->rooms[i].start)
			printf("Start\n");
		else if (map->rooms[i].end)
			printf("End\n");
		j = -1;
		printf("%d - num_of_links\n", map->rooms[i].num_of_links);
		while (++j < map->rooms[i].num_of_links && map->rooms[i].links)
			printf("%s\n", map->rooms[map->rooms[i].links[j]].name);
	}
	printf("----------------\n");
}

void			free_map(t_map **map)
{
	if (!map || !*map)
		return ;
	free_rooms(&(*map)->rooms, (*map)->num_of_rooms);
	free(*map);
	map = 0;
}
