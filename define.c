/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshellie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 20:17:12 by lshellie          #+#    #+#             */
/*   Updated: 2019/08/23 20:17:13 by lshellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		is_link(char *line)
{
	char	**split;
	int 	i;

	i = 0;
	if (line[0] == '#')
		return (0);
	if (!(split = ft_strsplit(line, '-')))
		return (0);
	while (split[i])
		++i;
	ft_free_split(split, i);
	if (i == 2)
		return (1);
	return (0);
}

int		is_room(char *line)
{
	char	**split;
	int 	i;

	i = 0;
	if (line[0] == '#')
		return (0);
	if (!(split = ft_strsplit(line, ' ')))
		return (0);
	while (split[i])
		++i;
	ft_free_split(split, i);
	if (i == 3)
		return (1);
	return (0);
}

int		is_ant(char *line)
{
	while (*line)
	{
		if (!ft_isdigit(*line))
			return (0);
		++line;
	}
	return (1);
}