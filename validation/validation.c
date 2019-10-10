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

#include "../lem_in.h"

int		check_start_end(t_map *nest)
{
	int		i;

	i = -1;
	while (++i < nest->num_of_rooms)
	{
		if ((nest->rooms[i].end
		|| nest->rooms[i].start) && !nest->rooms[i].num_of_links)
			return (0);
	}
	return (1);
}

int		check_duplicates(t_room *rooms, int num)
{
	int		i;
	int		j;

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
	int		i;

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
	char	**split;
	int		mas[3];

	if (!map)
		return (0);
	if (!(split = ft_strsplit(map, '\n')))
		return (0);
	if (!(check_order(split, mas)))
		return (0);
	if (!check_part1(split, mas) || !check_part2(split, mas) \
	|| !check_part3(split, mas) || !check_part4(split))
		return (0);
	free_split(split);
	return (1);
}
