/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_and_save.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshellie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 16:30:42 by lshellie          #+#    #+#             */
/*   Updated: 2019/08/23 16:30:43 by lshellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

int			count_rooms(char **split)
{
	int		i;
	int		num;

	i = -1;
	num = 0;
	while (split[++i])
	{
		if (is_room(split[i]))
			++num;
	}
	return (num);
}

t_map		*make_map(char *map)
{
	t_map		*new_map;
	char		**split;

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

char		*ft_free_split(char **split, int num)
{
	int		i;

	i = 0;
	while (i < num)
	{
		free(split[i]);
		++i;
	}
	free(split);
	return (0);
}

static char	*ft_strjoin_n(char *s1, char *s2)
{
	unsigned int	len1;
	unsigned int	len2;
	char			*str;
	unsigned int	len;
	unsigned int	i;

	i = -1;
	if (s1 == 0 || s2 == 0)
		return (0);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	len = len1 + len2 + 1 + 1;
	if (!(str = (char *)ft_memalloc(sizeof(str) * len)))
		return (0);
	while (++i < len1)
		str[i] = s1[i];
	str[i++] = '\n';
	while (i < len)
		str[i++] = *s2++;
	str[len] = 0;
	free(s1);
	return (str);
}

char		*read_and_save(void)
{
	char	*map;
	char	*buf;
	int		ret;

	map = 0;
	buf = 0;
	while ((ret = get_next_line(0, &buf)) != 0)
	{
		if (ret < 0 || buf[0] == 0 ||
		buf[0] == 'L' || buf[0] == '-')
		{
			buf ? free(buf) : buf;
			map ? free(map) : 0;
			return (0);
		}
		if (!map)
			map = ft_strdup(buf);
		else
			map = ft_strjoin_n(map, buf);
		free(buf);
	}
	map = ft_strjoin_n(map, "\0");
	return (map);
}
