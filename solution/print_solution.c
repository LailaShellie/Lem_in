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

	cur_way = lst->ways;
	while (cur_way)
	{
		cur_node = cur_way->nodes_end;
		while (cur_node)
		{
			if (cur_node->prev)
				cur_node->ant = cur_node->prev->ant;
			else if (!cur_node->prev && lst->ants < lst->all_ants)
				cur_node->ant = ++lst->ants;
			else if (!cur_node->prev && lst->ants >= lst->all_ants)
				cur_node->ant = 0;
			cur_node->visited = 0;
			cur_node = cur_node->prev;
		}
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
		cur_way->num_of_ants = cur_way->turns
				? cur_way->turns - cur_way->len : 0;
		cur_node = cur_way->nodes_start;
		while (cur_node->next)
			cur_node = cur_node->next;
		cur_way->nodes_end = cur_node;
		cur_way = cur_way->next;
		++lst->num_of_sets;
	}
}

void	while_node(t_map *nest, t_ways *cur_way, int *fl)
{
	t_nodes		*cur_node;

	cur_node = cur_way->nodes_end;
	while (cur_node)
	{
		if (!cur_node->visited && cur_node->ant)
		{
			if (*fl == 1)
				write(1, " ", 1);
			ft_putstr("L");
			ft_putnbr(cur_node->ant);
			ft_putstr("-");
			ft_putstr(nest->rooms[cur_node->num].name);
			*fl = 1;
			cur_node->visited = 1;
			cur_node = cur_way->nodes_start;
		}
		cur_node = cur_node->prev;
	}
}

int		print_solution(t_lst *lst, t_map *nest)
{
	t_ways		*cur_way;
	int			i;
	int			fl;

	find_ends(lst);
	lst->all_ants = nest->ants;
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
				while_node(nest, cur_way, &fl);
				cur_way = cur_way->next;
			}
		}
		write(1, "\n", 1);
	}
	return (0);
}
