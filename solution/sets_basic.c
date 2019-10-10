/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sets_basic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshellie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 12:49:06 by lshellie          #+#    #+#             */
/*   Updated: 2019/09/21 12:49:07 by lshellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

t_ways		*new_set(t_map *nest, int cur)
{
	t_ways		*new;

	if (!(new = ft_memalloc(sizeof(t_ways))))
		return (0);
	return (new);
}

void		put_set(t_lst *lst, t_ways *new)
{
	t_ways		*cur;
	t_ways		*prev;

	prev = 0;
	if (!lst->ways)
	{
		lst->ways = new;
		return ;
	}
	cur = lst->ways;
	while (cur)
	{
		if (new->len < cur->len)
		{
			new->next = cur;
			if (prev)
				prev->next = new;
			else
				lst->ways = new;
			return ;
		}
		prev = cur;
		cur = cur->next;
	}
	prev ? prev->next = new : 0;
}

t_lst		*new_lst(void)
{
	t_lst		*new;

	if (!(new = (t_lst *)ft_memalloc(sizeof(t_lst))))
		return (0);
	return (new);
}

void		set_new_set(t_map *map, t_lst *new)
{
	t_lst	*tmp;

	if (!map->sets)
		map->sets = new;
	else
	{
		if (map->sets->sum > new->sum)
		{
			tmp = map->sets;
			map->sets = new;
			free_sets(tmp);
		}
		else
			free_sets(new);
	}
}
