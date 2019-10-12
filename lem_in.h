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
# include <stdio.h>
# define ANTS 0
# define ROOMS 1
# define LINKS 2

typedef struct		s_queue
{
	int				i;
	int				weight;
	struct s_queue	*next;
}					t_queue;

typedef struct		s_nodes
{
	int				num;
	int				ant;
	int				visited;
	struct s_nodes	*next;
	struct s_nodes	*prev;
}					t_nodes;

typedef struct		s_ways
{
	t_nodes			*nodes_start;
	t_nodes			*nodes_end;
	int				len;
	int				num_of_ants;
	int				turns;
	struct s_ways	*next;
}					t_ways;

typedef struct		s_lst
{
	int				max_len;
	int				sum;
	int				ants;
	int				all_ants;
	int				num_of_sets;
	t_ways			*ways;
}					t_lst;

typedef struct		s_links
{
	char			**first;
	char			**second;
}					t_links;

typedef struct		s_room
{
	char			*name;
	int				x;
	int				y;
	int				start;
	int				end;
	int				num_of_links;
	int				*links;
	int				weight;
	int				sh;
	int 			color;
	int 			visited;
}					t_room;

typedef struct		s_map
{
	int				ants;
	int				num_of_rooms;
	int				index_end;
	int				index_start;
	int				step;
	char 			*output;
	t_room			*rooms;
	int				*pipes;
	t_lst			*sets;
	t_queue			*queue;
}					t_map;

void				set_new_set(t_map *map, t_lst *new);
t_lst				*new_lst(void);
t_ways				*new_set(t_map *nest, int cur);
void				put_set(t_lst *lst, t_ways *new);
int					print_solution(t_lst *lst, t_map *nest);
t_map				*make_map(char *map);
void				free_rooms(t_room **rooms, int num);
void				free_map(t_map **map);
void				free_split(char **split);
void				free_sets(t_lst *lst);
char				*read_and_save(void);
char				*ft_free_split(char **split, int num);
int					validation(char *map);
int					check_duplicates(t_room *rooms, int num);
int					check_start_end(t_map *nest);
int					is_number(char *line);
int					is_room(char *line);
int					is_ant(char *line);
int					is_link(char *line);
int					find_links(char **split);
int					find_rooms(char **split);
int					find_ants(char **split);
int					find_index_by_name(t_room *rooms, int num, char *name);
int					check_part1(char **split, int *mas);
int					check_part2(char **split, int *mas);
int					check_part3(char **split, int *mas);
int					check_part4(char **split);
int					make_links(t_map *map, char **split);
void				link_rooms(t_map *map, t_links *links);
int					solution(t_map *map);
int					make_pipes(t_map *map);
int					find_way(t_map *map);
int					find_overlapping_ways(t_map *map, t_room *room);
int					count_rooms(char **split);
int					find_min_weight(t_map	*map, int cur);
void				clear_graph(t_map *map);
int					is_blocked(t_map *map, int cur, int next);
void				find_sets(t_map *nest);
int					make_set(t_map *nest, t_lst *lst, int cur);
int					calculate_turns(t_map *nest, t_lst *lst);
t_room				*make_rooms(char **split, int num);
int					find_start(t_map *nest);

#endif
