/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parts.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshellie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 13:19:04 by lshellie          #+#    #+#             */
/*   Updated: 2019/08/24 13:19:05 by lshellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

int		check_part4(char **split)
{
	int		i;
	int		start;
	int		end;

	end = 0;
	start = 0;
	i = -1;
	while (split[++i])
	{
		if (ft_strequ(split[i], "##start"))
		{
			if (!is_room(split[i + 1]) || start)
				return (0);
			++start;
		}
		else if (ft_strequ(split[i], "##end"))
		{
			if (!is_room(split[i + 1]) || end)
				return (0);
			++end;
		}
	}
	return (start + end == 2 ? 1 : 0);
}

int		check_part3(char **split, int *mas)
{
	int		i;

	i = mas[2];
	while (split[++i])
	{
		if (split[i][0] == '#')
			continue ;
		if (!is_link(split[i]))
			return (0);
	}
	return (1);
}

int		check_part2(char **split, int *mas)
{
	int		i;
	int		end;

	i = mas[1];
	end = mas[2];
	while (++i < end)
	{
		if (split[i][0] == '#')
			continue ;
		if (!is_room(split[i]))
			return (0);
	}
	return (1);
}

int		check_part1(char **split, int *mas)
{
	int		i;
	int		end;

	end = mas[1];
	i = -1;
	while (++i < end)
	{
		if (i == mas[0])
			continue ;
		if (split[i][0] != '#')
			return (0);
	}
	return (1);
}
