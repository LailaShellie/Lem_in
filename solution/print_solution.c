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
	t_sets		*cur_set;
	int 		order;

	order = 1;
	cur_set = lst->sets;
	while (cur_set)
	{
		cur_node = cur_set->nodes_end;
		while (cur_node)
		{
			if (cur_node->next)
				cur_node->next->ant = cur_node->ant;
			if (!cur_node->prev && cur_set->num_of_ants > 0)
			{
				--cur_set->num_of_ants;
				cur_node->ant += !cur_node->ant ? order : lst->num_of_sets;
				if (cur_node->ant > lst->all_ants)
					--cur_node->ant;
			}
			else if (!cur_node->prev && cur_set->num_of_ants <= 0)
				cur_node->ant = 0;
			cur_node->visited = 0;
			cur_node = cur_node->prev;
		}
		++order;
		cur_set = cur_set->next;
	}
}

void	find_ends(t_lst *lst)
{
	t_nodes		*cur_node;
	t_sets		*set;

	set = lst->sets;
	while (set)
	{
		if (set->len > lst->max_len)
			lst->max_len = set->len;
		set->num_of_ants = set->turns ? set->turns - set->len : 0;
		cur_node = set->nodes_start;
		while (cur_node->next)
			cur_node = cur_node->next;
		set->nodes_end = cur_node;
		set = set->next;
		++lst->num_of_sets;
	}
}

int 	print_solution(t_lst *lst, t_map *nest)
{
	t_nodes		*cur_node;
	t_sets		*cur_set;
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
			cur_set = lst->sets;
			while (cur_set)
			{
				cur_node = cur_set->nodes_end;
				while (cur_node)
				{
					if (!cur_node->visited && cur_node->ant)
					{
                        if (fl == 1)
                            printf(" ");
						printf("L%d-%s", cur_node->ant, nest->rooms[cur_node->num].name);
						fl = 1;
						cur_node->visited = 1;
						cur_node = cur_set->nodes_start;
					}
					cur_node = cur_node->prev;
				}
				cur_set = cur_set->next;
			}
		}
		printf("\n");
	}
	return (0);
}
