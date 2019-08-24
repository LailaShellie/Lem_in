/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshellie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 20:07:34 by lshellie          #+#    #+#             */
/*   Updated: 2019/08/23 20:07:35 by lshellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		find_links(char **split)
{
	int		i;

	i = 0;
	while (split[i])
	{
		if (!is_room(split[i]) && is_link(split[i]))
			return (i);
		++i;
	}
	return (-1);
}

int		find_rooms(char **split)
{
	int		i;

	i = 0;
	while (split[i])
	{
		if (is_room(split[i]))
			return (i);
		++i;
	}
	return (-1);
}

int		find_ants(char **split)
{
	int		i;

	i = 0;
	while (split[i])
	{
		if (is_ant(split[i]))
			return (i);
		++i;
	}
	return (-1);
}