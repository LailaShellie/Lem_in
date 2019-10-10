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

int			set_node(t_ways *new, int cur)
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
	int		i;
	t_ways	*new;

	if (!(new = new_set(nest, cur)))
		return (0);
	set_node(new, cur);
	i = -1;
	while (++i < nest->rooms[cur].num_of_links)
	{
		if ((nest->rooms[cur].sh &&
		nest->rooms[nest->rooms[cur].links[i]].sh == nest->rooms[cur].sh
			&& nest->rooms[nest->rooms[cur].links[i]].weight
			> nest->rooms[cur].weight)
			|| nest->rooms[cur].links[i] == nest->index_end)
		{
			set_node(new, nest->rooms[cur].links[i]);
			cur = nest->rooms[cur].links[i];
			++new->len;
			if (cur == nest->index_end)
				break ;
			i = -1;
		}
	}
	put_set(lst, new);
	return (1);
}

void		find_sets(t_map *nest)
{
	int		cur;
	int		i;
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
			}
			make_set(nest, new, nest->rooms[cur].links[i]);
		}
	}
	if (new)
	{
		calculate_turns(nest, new);
		set_new_set(nest, new);
	}
}
