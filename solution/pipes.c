/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshellie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 18:16:42 by lshellie          #+#    #+#             */
/*   Updated: 2019/10/03 18:16:43 by lshellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

int			make_pipes(t_map *map)
{
	int		*pipes;

	if (!(pipes = (int *)ft_memalloc(sizeof(int) * (map->num_of_rooms * map->num_of_rooms))))
		return (0);
	map->pipes = pipes;
	return (1);
}