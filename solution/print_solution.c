/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_solution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshellie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 12:38:25 by lshellie          #+#    #+#             */
/*   Updated: 2019/09/26 12:56:10 by lshellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

void	make_step(t_lst *lst)
{
	t_nodes		*cur_node;
	t_ways		*cur_way;
	int 		order;

	order = 1;
	cur_way = lst->ways;
	while (cur_way)
	{
		cur_node = cur_way->nodes_end;
		while (cur_node)
		{
			if (cur_node->next)
				cur_node->next->ant = cur_node->ant;
			if (!cur_node->prev && cur_way->num_of_ants > 0)
			{
				--cur_way->num_of_ants;
				cur_node->ant += !cur_node->ant ? order : lst->num_of_sets;
				if (cur_node->ant > lst->all_ants)
					--cur_node->ant;
			}
			else if (!cur_node->prev && cur_way->num_of_ants <= 0)
				cur_node->ant = 0;
			cur_node->visited = 0;
			cur_node = cur_node->prev;
		}
		++order;
		cur_way = cur_way->next;
	}
}

void	find_ends(t_lst *lst)
{
	t_nodes		*cur_node;
	t_ways		*cur_way;

	cur_way = lst->ways;
	while (cur_way)
	{
		if (cur_way->len > lst->max_len)
			lst->max_len = cur_way->len;
		cur_way->num_of_ants = cur_way->turns ? cur_way->turns - cur_way->len : 0;
		cur_node = cur_way->nodes_start;
		while (cur_node->next)
			cur_node = cur_node->next;
		cur_way->nodes_end = cur_node;
		cur_way = cur_way->next;
		++lst->num_of_sets;
	}
}

int 	print_solution(t_lst *lst, t_map *nest)
{
	t_nodes		*cur_node;
	t_ways		*cur_way;
	int 		i;
	int         fl;

	find_ends(lst);
	lst->all_ants = nest->ants;
	printf("%s\n", nest->str);
	while (lst->sum--)
	{
        fl = 0;
		make_step(lst);
		i = -1;
		while (++i <= lst->max_len)
		{
			cur_way = lst->ways;
			while (cur_way)
			{
				cur_node = cur_way->nodes_end;
				while (cur_node)
				{
					if (!cur_node->visited && cur_node->ant)
					{
						if (cur_node->ant <= lst->all_ants)
						{
							if (fl == 1)
								printf(" ");
							printf("L%d-%s", cur_node->ant, nest->rooms[cur_node->num].name);
							fl = 1;
						}
						cur_node->visited = 1;
						cur_node = cur_way->nodes_start;
					}
					cur_node = cur_node->prev;
				}
				cur_way = cur_way->next;
			}
		}
		printf("\n");
	}
	return (0);
}
