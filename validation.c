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

int		check_order(char **split)
{
	char 	mas[3];
	int 	i;

	i = -1;
	while (++i < 3)
		mas[i] = -1;
	mas[ANTS] = find_ants(split);
	mas[ROOMS] = find_rooms(split);
	mas[LINKS] = find_links(split);
	printf("%hhd\n%hhd\n%hhd\n", mas[ANTS], mas[ROOMS], mas[LINKS]);
	if (mas[ANTS] < 0 || mas[ANTS] > mas[ROOMS] || mas[ANTS] > mas[LINKS])
		return (0);
	if (mas[ROOMS] < 0 || mas[ROOMS] > mas[LINKS])
		return (0);
	return (1);
}

int		check_map(char *map)
{
	int 	i;
	char 	**split;

	i = 0;
	if (!map)
		return (0);
	if (!(split = ft_strsplit(map, '\n')))
		return (0);
	if (!(check_order(split)))
		return (0);
	return (1);
}
