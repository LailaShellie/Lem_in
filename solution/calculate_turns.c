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
	t_sets		*cur_set;

	lst->sum = 0;
	cur_set = lst->sets;
	while (cur_set)
	{
		if (cur_set->turns < cur_set->len)
			lst->bad = 1;
		if (cur_set->turns > lst->sum)
			lst->sum = cur_set->turns;
		cur_set = cur_set->next;
	}
}

int		is_sorted(t_sets *sets)
{
	t_sets		*cur_set;

	cur_set = sets;
	while (cur_set && cur_set->next)
	{
		if (cur_set->next->turns && cur_set->turns > cur_set->next->turns)
			return (0);
		if (!cur_set->next->turns && cur_set->turns > cur_set->next->len)
			return (0);
		cur_set = cur_set->next;
	}
	return (1);
}

int 	calculate_turns(t_map *nest, t_lst *lst)
{
	t_sets		*cur_set;

	cur_set = lst->sets;
	cur_set->turns = nest->ants + cur_set->len;
	while (!is_sorted(lst->sets))
	{
		cur_set = lst->sets;
		while (cur_set && cur_set->next)
		{
			if (!cur_set->next->turns && cur_set->turns > cur_set->next->len)
			{
				--cur_set->turns;
				cur_set->next->turns = cur_set->next->len + 1;
			}
			while (cur_set->next->turns && cur_set->turns > cur_set->next->turns)
			{
				--cur_set->turns;
				++cur_set->next->turns;
			}
			cur_set = cur_set->next;
		}
	}
	find_max(lst);
	return (0);
}