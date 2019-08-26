/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshellie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 14:17:08 by lshellie          #+#    #+#             */
/*   Updated: 2019/08/24 14:17:10 by lshellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int 		count_rooms(char **split)
{
	int		i;
	int 	num;

	i = -1;
	num = 0;
	while (split[++i])
		if (is_room(split[i]))
			++num;
	return (num);
}

void		get_name_x_y(t_room *room, char *line)
{
	char 	**split;

	if (!(split = ft_strsplit(line, ' ')))
		return ;
	room->name = ft_strdup(split[0]);
	room->x = ft_atoi(split[1]);
	room->y = ft_atoi(split[2]);
}

t_room		*make_rooms(char **split, int num)
{
	t_room		*rooms;
	int 		i;
	int 		j;

	j = 0;
	i = -1;
	if (!(rooms = (t_room *)ft_memalloc(sizeof(t_room) * num)))
		return (0);
	while (split[++i])
	{
		if (ft_strequ(split[i], "##start"))
			rooms[j].start = 1;
		if (ft_strequ(split[i], "##end"))
			rooms[j].end = 1;
		if (is_room(split[i]))
			get_name_x_y(&rooms[j++], split[i]);
	}
	if (!(check_duplicates(rooms, num)))
		free_rooms(&rooms, num);
	return (rooms);
}

t_map		*make_map(char *map)
{
	t_map		*new_map;
	char 		**split;

	if (!(new_map = (t_map *)ft_memalloc(sizeof(t_map))) \
	|| !(split = ft_strsplit(map, '\n')))
		return (0);
	new_map->ants = ft_atoi(split[find_ants(split)]);
	new_map->num_of_rooms = count_rooms(split);
	if (!(new_map->rooms = make_rooms(split, new_map->num_of_rooms)))
	{
		free_map(&new_map);
		return (0);
	}
	if (!make_links(new_map->rooms, split, new_map->num_of_rooms))
	{
		free_map(&new_map);
		return (0);
	}
	show_map(new_map);
	return (new_map);
}
