/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshellie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 17:03:28 by lshellie          #+#    #+#             */
/*   Updated: 2019/08/22 17:03:29 by lshellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			error(t_map *nest)
{
	if (nest)
		free_map(&nest);
	ft_putstr("Error\n");
	return (0);
}

int			main(void)
{
	char	*map;
	t_map	*nest;

	nest = 0;
	map = read_and_save();
	if (!(validation(map)))
		return (error(nest));
	if (!(nest = make_map(map)))
		return (error(nest));
	if (!check_start_end(nest))
		return (error(nest));
	ft_putendl(map);
	if (!(solution(nest)))
		return (error(nest));
	free_map(&nest);
	free(map);
	return (0);
}
