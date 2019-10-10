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

#include "../lem_in.h"

int			count_num_of_links(t_map *map, t_links *links)
{
	int		i;
	int		n1;
	int		n2;

	i = -1;
	while (links->first[++i])
	{
		if (links->first[i][0] == '#' || links->second[i][0] == '#')
			continue ;
		n1 = find_index_by_name(map->rooms,
				map->num_of_rooms, links->first[i]);
		n2 = find_index_by_name(map->rooms,
				map->num_of_rooms, links->second[i]);
		if (n1 < 0 || n2 < 0)
			return (0);
		map->rooms[n1].num_of_links += 1;
		map->rooms[n2].num_of_links += 1;
	}
	return (1);
}

int			count_links(char **split)
{
	int		i;
	int		num;

	i = -1;
	num = 0;
	while (split[++i])
		if (is_link(split[i]))
			++num;
	return (num);
}

void		set_links(t_links *links, char **split)
{
	int		i;
	int		j;
	int		num;
	char	*minus;

	j = 0;
	i = -1;
	num = 1 + count_links(split);
	links->first = ft_memalloc(num * sizeof(char *));
	links->second = ft_memalloc(num * sizeof(char *));
	links->first[num - 1] = 0;
	links->second[num - 1] = 0;
	while (split[++i])
	{
		if (is_link(split[i]))
		{
			minus = ft_strchr(split[i], '-');
			*minus = 0;
			links->first[j] = ft_strdup(split[i]);
			links->second[j] = ft_strdup(minus + 1);
			++j;
		}
	}
}

int			check_links_duplicates(t_links *links)
{
	int		i;
	int		j;

	i = -1;
	while (links->first[++i])
	{
		if (!ft_strcmp(links->first[i], links->second[i]))
			return (0);
		j = i;
		while (links->first[++j])
		{
			if ((!ft_strcmp(links->first[i], links->first[j])
			&& !ft_strcmp(links->second[i], links->second[j])) ||
			(!ft_strcmp(links->second[i], links->first[j])
			&& !ft_strcmp(links->first[i], links->second[j])))
			{
				links->first[i][0] = '#';
				links->second[i][0] = '#';
			}
		}
	}
	return (1);
}

int			make_links(t_map *map, char **split)
{
	t_links	links;

	set_links(&links, split);
	if (!(check_links_duplicates(&links)))
		return (0);
	if (!(count_num_of_links(map, &links)))
	{
		return (0);
	}
	link_rooms(map, &links);
	free_split(links.second);
	free_split(links.first);
	return (1);
}
