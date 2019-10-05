/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_turns.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshellie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 13:47:47 by lshellie          #+#    #+#             */
/*   Updated: 2019/09/25 13:47:48 by lshellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

void 	find_max(t_lst *lst)
{
	t_ways		*cur_way;

	lst->sum = 0;
	cur_way = lst->ways;
	while (cur_way)
	{
		if (cur_way->turns < cur_way->len)
			lst->bad = 1;
		if (cur_way->turns > lst->sum)
			lst->sum = cur_way->turns;
		cur_way = cur_way->next;
	}
}

int		is_sorted(t_ways *ways)
{
	t_ways		*cur_way;

	cur_way = ways;
	while (cur_way && cur_way->next)
	{
		if (cur_way->next->turns && cur_way->turns > cur_way->next->turns)
			return (0);
		if (!cur_way->next->turns && cur_way->turns > cur_way->next->len)
			return (0);
		cur_way = cur_way->next;
	}
	return (1);
}

int 	calculate_turns(t_map *nest, t_lst *lst)
{
	t_ways		*cur_way;

	cur_way = lst->ways;
	cur_way->turns = nest->ants + cur_way->len;
	while (!is_sorted(lst->ways))
	{
		cur_way = lst->ways;
		while (cur_way && cur_way->next)
		{
			if (!cur_way->next->turns && cur_way->turns > cur_way->next->len)
			{
				--cur_way->turns;
				cur_way->next->turns = cur_way->next->len + 1;
			}
			while (cur_way->next->turns && cur_way->turns > cur_way->next->turns)
			{
				--cur_way->turns;
				++cur_way->next->turns;
			}
			cur_way = cur_way->next;
		}
	}
	find_max(lst);
	return (0);
}