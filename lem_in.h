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

typedef struct		s_room
{
	char 			*name;
	int 			x;
	int 			y;
	int 			start;
	int 			end;
	int 			num_of_links;
	int 			*links;
}					t_room;

typedef struct		s_map
{
	int 			ants;
	int 			num_of_rooms;
	t_room			*rooms;
}					t_map;

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
int 	check_links(char **split);

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

/*
 * check_parts.c
 */

int 	check_part1(char **split, int *mas);
int 	check_part2(char **split, int *mas);
int 	check_part3(char **split, int *mas);
int 	check_part4(char **split);

#endif
