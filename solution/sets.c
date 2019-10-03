/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sets.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshellie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 14:40:15 by lshellie          #+#    #+#             */
/*   Updated: 2019/09/21 14:40:17 by lshellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

void		ft_show_sets(t_map *nest)
{
	t_lst		*cur_lst;
	t_sets		*cur_set;
	t_nodes		*cur_node;

	cur_lst = nest->sets;
	while (cur_lst)
	{
		cur_set = cur_lst->sets;
		while (cur_set)
		{
			cur_node = cur_set->nodes_start;
			while (cur_node)
			{
				printf("%s ", nest->rooms[cur_node->num].name);
				cur_node = cur_node->next;
			}
			printf("len - %d ants = %d turns - %d bad  - %d\n", cur_set->len + 1, cur_set->turns ? cur_set->turns - cur_set->len : 0, cur_set->turns, cur_lst->bad);
			cur_set = cur_set->next;
		}
		printf("sum - %d\n", cur_lst->sum);
		printf("------\n");
		cur_lst = cur_lst->next;
	}
}

int 		set_node(t_sets *new, int cur)
{
	t_nodes		*cur_node;

	if (!new->nodes_start)
	{
		new->nodes_start = ft_memalloc(sizeof(t_nodes));
		new->nodes_start->num = cur;
	}
	else
	{
		cur_node = new->nodes_start;
		while (cur_node->next)
			cur_node = cur_node->next;
		cur_node->next = ft_memalloc(sizeof(t_nodes));
		cur_node->next->prev = cur_node;
		cur_node->next->num = cur;
	}
	return (1);
}

int			make_set(t_map *nest, t_lst *lst, int cur)
{
	int 	i;
	t_sets	*new;

	if (!(new = new_set(nest, cur)))
		return (0);
	set_node(new, cur);
	i = -1;
	while (++i < nest->rooms[cur].num_of_links)
	{
		if ((nest->rooms[nest->rooms[cur].links[i]].sh == nest->rooms[cur].sh
			 && nest->rooms[nest->rooms[cur].links[i]].weght == nest->rooms[cur].weght + 1)
			 || nest->rooms[cur].links[i] == nest->index_end)
		{
			set_node(new, nest->rooms[cur].links[i]);
			cur = nest->rooms[cur].links[i];
			++new->len;
			i = -1;
		}
	}
	put_set(lst, new);
	return (1);
}

void 		find_sets(t_map *nest)
{
	int 	cur;
	int 	i;
	t_lst	*new;

	new = 0;
	cur = nest->index_start;
	i = -1;
	while (++i < nest->rooms[cur].num_of_links)
	{
		if (nest->rooms[nest->rooms[cur].links[i]].sh != 0)
		{
			if (!new)
			{
				if (!(new = new_lst()))
					return ;
				set_new_set(&nest->sets, new);
			}
			make_set(nest, new, nest->rooms[cur].links[i]);
		}
	}
	calculate_turns(nest, new);
}