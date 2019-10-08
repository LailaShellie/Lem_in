/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshellie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 17:02:38 by lshellie          #+#    #+#             */
/*   Updated: 2019/08/22 17:02:39 by lshellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_LEM_IN_H
# define LEM_IN_LEM_IN_H
# include "libft/libft.h"

#include <stdio.h>

# define ANTS 0
# define ROOMS 1
# define LINKS 2

typedef struct		s_queue
{
	int 			i;
	int 			weight;
	struct s_queue	*next;
}					t_queue;

typedef struct		s_nodes
{
	int 			num;
	int 			ant;
	int 			visited;
	struct s_nodes	*next;
	struct s_nodes	*prev;
}					t_nodes;

typedef struct		s_ways
{
	t_nodes			*nodes_start;
	t_nodes			*nodes_end;
	int 			num_of_ants;
	int 			len;
	int 			turns;
	struct s_ways	*next;
}					t_ways;

typedef struct		s_lst
{
	int 			max_len;
	int 			sum;
	int 			all_ants;
	int 			bad;
	int 			num_of_sets;
	t_ways			*ways;
	struct s_lst	*next;
}					t_lst;

typedef struct		s_links
{
	char 			**first;
	char 			**second;
}					t_links;

typedef struct		s_room
{
	char 			*name;
	int 			x;
	int 			y;
	int 			start;
	int 			end;
	int 			num_of_links;
	int 			*links;
	int				weight;
	int				sh;
	int				visited;
	int 			color;
}					t_room;

typedef struct		s_pipe
{
	int				status;
	int 			forb;
	int				good;
}					t_pipe;

typedef struct		s_map
{
	int 			ants;
	int 			num_of_rooms;
	int 			num_of_ways;
	int 			index_end;
	int 			index_start;
	int				step;
	t_room			*rooms;
	t_pipe			*pipes;
	t_lst			*sets;
	t_queue			*queue;
	char 			*str;
}					t_map;

/*
 * set_basic.c
 */

void		ft_show_sets(t_map *nest);
void		set_new_set(t_lst **lst, t_lst *new);
t_lst		*new_lst(void);
void		free_lst(t_lst *lst);
t_ways		*new_set(t_map *nest, int cur);
void		put_set(t_lst *lst, t_ways *new);
int 		print_solution(t_lst *lst, t_map *nest);

/*
 *  make_map.c
 */

t_map		*make_map(char *map);

/*
 * free.c
 */

void		free_rooms(t_room **rooms, int num);
void		free_map(t_map **map);
void		show_map(t_map *map);
void		free_split(char **split);
void		free_sets(t_lst *lst);

/*
 * read_and_save.c
 */

char 			*read_and_save(void);
char			*ft_free_split(char **split, int num);

/*
 * validation.c
 */

int		validation(char *map);
int 	check_duplicates(t_room *rooms, int num);
int     check_start_end(t_map *nest);

/*
 * define.c
 */

int		is_number(char *line);
int		is_room(char *line);
int		is_ant(char *line);
int		is_link(char *line);

/*
 * find.c
 */

int		find_links(char **split);
int		find_rooms(char **split);
int		find_ants(char **split);
int 	find_index_by_name(t_room *rooms, int num, char *name);
int		find_start(t_map *nest);

/*
 * check_parts.c
 */

int 	check_part1(char **split, int *mas);
int 	check_part2(char **split, int *mas);
int 	check_part3(char **split, int *mas);
int 	check_part4(char **split);

/*
 * make_links.c
 */

int 		make_links(t_map *map, char **split);
void		link_rooms(t_map *map, t_links *links);

/*
 * solution_main.c
 */

int			solution(t_map *map);
int			dijkstra(t_map *map);
int			make_pipes(t_map *map);
int			show_pipes(t_map *map);
int			remove_dead_pipes(t_map *map);
int			find_way(t_map *map);
int			find_overlapping_ways(t_map *map);
int			find_min_weight(t_map	*map, int cur);
void		clear_graph(t_map *map);

/*
 * sets.c
 */

void 		find_sets(t_map *nest);
int			make_set(t_map *nest, t_lst *lst, int cur);
int 		count_sets_len(t_map *nest, int cur);
int			calculate_turns(t_map *nest, t_lst *lst);
void		ft_show_set(t_map *nest);


#endif
