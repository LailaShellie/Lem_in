/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshellie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 15:02:58 by lshellie          #+#    #+#             */
/*   Updated: 2019/08/23 15:03:00 by lshellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		check_duplicates_links(char **split, int i)
{
	char	*link;
	char	**split_link1;
	char	**split_link2;

	link = split[i];
	while (split[++i])
	{
		split_link1 = ft_strsplit(link, '-');
		split_link2 = ft_strsplit(split[i], '-');
		if ((ft_strequ(split_link1[0], split_link2[0]) && ft_strequ(split_link1[1], split_link2[1]))
		|| (ft_strequ(split_link1[1], split_link2[0]) && ft_strequ(split_link1[0], split_link2[1]))
		|| (ft_strequ(split_link1[0], split_link2[1]) && ft_strequ(split_link1[1], split_link2[0])))
		{
			ft_free_split(split_link1, 2);
			ft_free_split(split_link2, 2);
			return (0);
		}
		ft_free_split(split_link1, 2);
		ft_free_split(split_link2, 2);
	}
	return (1);
}

int 	check_links(char **split)
{
	int 	i;

	i = -1;
	while (split[++i])
	{
		if (is_link(split[i]))
		{
			if (!(check_duplicates_links(split, i)))
				return (0);
		}
	}
	return (1);
}

int 	check_duplicates(t_room *rooms, int num)
{
	int 	i;
	int 	j;

	i = -1;
	while (++i < num - 1)
	{
		j = i;
		while (++j < num)
		{
			if (ft_strequ(rooms[i].name, rooms[j].name))
				return (0);
			if (rooms[i].x == rooms[j].x && rooms[i].y == rooms[j].y)
				return (0);
		}
	}
	return (1);
}

int		check_order(char **split, int *mas)
{
	int 	i;

	i = -1;
	while (++i < 3)
		mas[i] = -1;
	mas[ANTS] = find_ants(split);
	mas[ROOMS] = find_rooms(split);
	mas[LINKS] = find_links(split);
	if (mas[ANTS] < 0 || mas[ANTS] > mas[ROOMS] || mas[ANTS] > mas[LINKS])
		return (0);
	if (mas[ROOMS] < 0 || mas[ROOMS] > mas[LINKS])
		return (0);
	return (1);
}

int		validation(char *map)
{
	char 	**split;
	int 	mas[3];

	if (!map)
		return (0);
	if (!(split = ft_strsplit(map, '\n')))
		return (0);
	if (!(check_order(split, mas)))
		return (0);
	if (!check_part1(split, mas) || !check_part2(split, mas) \
	|| !check_part3(split, mas) || !check_part4(split))
		return (0);
//	printf("%d\n%d\n%d\n", ++mas[ANTS], ++mas[ROOMS], ++mas[LINKS]);
	return (1);
}
