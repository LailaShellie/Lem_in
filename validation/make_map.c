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

#include "../lem_in.h"

void		init_link_mas(t_map *map, int n1, int n2)
{
	int 	i;

	i = -1;
	if (!map->rooms[n1].links)
	{
		map->rooms[n1].links = ft_memalloc(map->rooms[n1].num_of_links * sizeof(int));
		while (++i < map->rooms[n1].num_of_links)
			map->rooms[n1].links[i] = -1;
	}
	i = -1;
	if (!map->rooms[n2].links)
	{
		map->rooms[n2].links = ft_memalloc(map->rooms[n2].num_of_links * sizeof(int));
		while (++i < map->rooms[n2].num_of_links)
			map->rooms[n2].links[i] = -1;
	}
}

void		init_link(t_map *map, int n1, int n2)
{
	int j;

	j = -1;
	init_link_mas(map, n1, n2);
	while (++j < map->rooms[n2].num_of_links)
	{
		if (map->rooms[n2].links[j] == -1)
		{
			map->rooms[n2].links[j] = n1;
			break ;
		}
	}
	j = -1;
	while (++j < map->rooms[n1].num_of_links)
	{
		if (map->rooms[n1].links[j] == -1)
		{
			map->rooms[n1].links[j] = n2;
			break ;
		}
	}
}

void		link_rooms(t_map *map, t_links *links)
{
	int 	i;
	int 	n1;
	int 	n2;

	i = -1;
	while (links->first[++i])
	{
		if (links->first[i][0] == '#' || links->second[i][0] == '#')
			continue ;
		n1 = find_index_by_name(map->rooms, map->num_of_rooms, links->first[i]);
		n2 = find_index_by_name(map->rooms, map->num_of_rooms, links->second[i]);
		init_link(map, n1, n2);
	}
}

int 		count_rooms(char **split)
{
	int		i;
	int 	num;

	i = -1;
	num = 0;
	while (split[++i])
	{
		if (is_room(split[i]))
			++num;
	}
	return (num);
}

int			get_name_x_y(t_room *room, char *line)
{
	char 	**split;

	if (!(split = ft_strsplit(line, ' ')))
		return (0);
	if (!(room->name = ft_strdup(split[0])))
		return (0);
	room->x = ft_atoi(split[1]);
	room->y = ft_atoi(split[2]);
	free_split(split);
	return (1);
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
			if (!get_name_x_y(&rooms[j++], split[i]))
				return (0);
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
	if (!make_links(new_map, split))
	{
		free_map(&new_map);
		return (0);
	}
	free_split(split);
	return (new_map);
}
