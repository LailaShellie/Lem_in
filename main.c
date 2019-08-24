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

int		main()
{
	char	*map;
	t_map	*nest;

	map = read_and_save();
	if (!(validation(map)))
	{
		ft_putstr("Error\n");
		return (0);
	}
	if (!(nest = make_map(map)))
	{
		ft_putstr("Error\n");
		return (0);
	}
	free_map(&nest);
	return (0);
}