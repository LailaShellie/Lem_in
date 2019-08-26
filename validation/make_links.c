/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_links.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshellie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 16:54:41 by lshellie          #+#    #+#             */
/*   Updated: 2019/08/24 17:06:02 by lshellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		link_rooms(t_room *rooms, char **split, int num)
{
	int 	i;
	int 	j;
	int 	k;

	k = -1;
	i = find_index_by_name(rooms, num, split[0]);
	j = find_index_by_name(rooms, num, split[1]);
	while (++k < rooms[i].num_of_links)
	{
		if (rooms[i].links[k] == -1)
		{
			rooms[i].links[k] = j;
			break ;
		}
	}
	k = -1;
	while (++k < rooms[j].num_of_links)
	{
		if (rooms[j].links[k] == -1)
		{
			rooms[j].links[k] = i;
			break ;
		}
	}
}

void		set_links(t_room *rooms, char **split, int num)
{
	int 	i;
	char 	**split_link;

	i = -1;
	while (split[++i])
	{
		if (is_link(split[i]))
		{
			split_link = ft_strsplit(split[i], '-');
			link_rooms(rooms, split_link, num);
			ft_free_split(split_link, 2);
		}
	}
}

int 		split_link(char *line, t_room *rooms, int num)
{
	char 	**split;
	int 	i;
	int 	j;

	if (!(split = ft_strsplit(line, '-')))
		return (0);
	i = find_index_by_name(rooms, num, split[0]);
	j = find_index_by_name(rooms, num, split[1]);
	if (i == j || i < 0 || j < 0)
		return (0);
	rooms[i].num_of_links += 1;
	rooms[j].num_of_links += 1;
	ft_free_split(split, 2);
	return (1);
}

int 		make_links(t_room *rooms, char **split, int num)
{
	int 	i;
	int 	j;

	i = -1;
	if (!(check_links(split)))
		return (0);
	while (split[++i])
	{
		if (is_link(split[i]))
		{
			if (!split_link(split[i], rooms, num))
				return (0);
		}
	}
	i = -1;
	while (++i < num)
	{
//		if (!(rooms[i].links = (int *)ft_memalloc(sizeof(int) * rooms[i].num_of_links)))
//			return (0);
		rooms[i].links = (int *)ft_memalloc(sizeof(int) * rooms[i].num_of_links);
		j = -1;
		while (++j < rooms[i].num_of_links)
			rooms[i].links[j] = -1;
	}
	set_links(rooms, split, num);
	return (1);
}
