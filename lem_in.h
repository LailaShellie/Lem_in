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
# define COMMAND 3
# define COMMENT 4

/*
 * read_and_save.c
 */
char 			*read_and_save(void);
char			*ft_free_split(char **split, int num);

/*
 * validation.c
 */

int				check_map(char *map);

/*
 * define.c
 */

int		is_room(char *line);
int		is_ant(char *line);
int		is_link(char *line);

/*
 * find.c
 */

int		find_links(char **split);
int		find_rooms(char **split);
int		find_ants(char **split);

#endif
