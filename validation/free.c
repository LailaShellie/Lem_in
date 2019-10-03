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

#include "../lem_in.h"

void		free_sets(t_lst *lst)
{
	t_sets		*cur_set;
	t_lst		*tmp_lst;
	t_nodes		*tmp_nodes;
	t_sets		*tmp_set;

	while (lst)
	{
		cur_set = lst->sets;
		while (cur_set)
		{
			while (cur_set->nodes_start)
			{
				tmp_nodes = cur_set->nodes_start;
				cur_set->nodes_start = cur_set->nodes_start->next;
				free(tmp_nodes);
			}
			tmp_set = cur_set;
			cur_set = cur_set->next;
			free(tmp_set);
		}
		tmp_lst = lst;
		lst = lst->next;
		free(tmp_lst);
	}
}

void		free_split(char **split)
{
	int 	i;

	i = 0;
	while (split[i])
		++i;
	ft_free_split(split, i);
}

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
		printf("%d - weight %d - num_of_links\n", map->rooms[i].weght, map->rooms[i].num_of_links);
		while (++j < map->rooms[i].num_of_links && map->rooms[i].links)
			printf("%s\n", map->rooms[map->rooms[i].links[j]].name);
		printf("sh - %d\n", map->rooms[i].sh);
	}
	printf("----------------\n");
}

void			free_map(t_map **map)
{
	if (!map || !*map)
		return ;
	free_rooms(&(*map)->rooms, (*map)->num_of_rooms);
	free((*map)->ways);
	free_sets((*map)->sets);
	free((*map)->str);
	free(*map);
	*map = 0;
}
