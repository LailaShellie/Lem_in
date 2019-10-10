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

void	free_sets(t_lst *lst)
{
	t_ways		*cur_way;
	t_nodes		*tmp_nodes;
	t_ways		*tmp_set;

	cur_way = lst->ways;
	while (cur_way)
	{
		while (cur_way->nodes_start)
		{
			tmp_nodes = cur_way->nodes_start;
			cur_way->nodes_start = cur_way->nodes_start->next;
			free(tmp_nodes);
		}
		tmp_set = cur_way;
		cur_way = cur_way->next;
		free(tmp_set);
	}
	free(lst);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		++i;
	ft_free_split(split, i);
}

void	free_rooms(t_room **rooms, int num)
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

void	free_map(t_map **map)
{
	if (!map || !*map)
		return ;
	free_rooms(&(*map)->rooms, (*map)->num_of_rooms);
	free_sets((*map)->sets);
	free((*map)->pipes);
	free(*map);
	*map = 0;
}
