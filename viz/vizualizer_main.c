/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vizualizer_main.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshellie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 12:56:33 by lshellie          #+#    #+#             */
/*   Updated: 2019/08/25 12:56:36 by lshellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vizualizer.h"

static char	*ft_strjoin_n(char *s1, char *s2)
{
	unsigned int	len1;
	unsigned int	len2;
	char			*str;
	unsigned int	len;
	unsigned int	i;

	i = -1;
	if (s1 == 0 || s2 == 0)
		return (0);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	len = len1 + len2 + 1 + 1;
	if (!(str = (char *)ft_memalloc(sizeof(str) * len)))
		return (0);
	while (++i < len1)
		str[i] = s1[i];
	str[i++] = '\n';
	while (i < len)
		str[i++] = *s2++;
	str[len] = 0;
	free(s1);
	return (str);
}

static char		*read_input(void)
{
	char	*map;
	char	*buf;
	int 	ret;

	map = 0;
	buf = 0;
	while ((ret = get_next_line(0, &buf)) != 0)
	{
		if (!map)
			map = ft_strdup(buf);
		else
			map = ft_strjoin_n(map, buf);
		free(buf);
	}
	map = ft_strjoin_n(map, "\0");
	return (map);
}

static char 	*get_turns(char *input)
{
	char 	*turns;
	int 	i;

	i = -1;
	while (input[++i])
	{
		if (input[i] == 'L')
			break ;
	}
	turns = ft_strdup(&input[i]);
	input[i] = 0;
	return (turns);
}

int 			main()
{
	char	*input;
	char 	*turns;
	char 	*map;
	t_map	*nest;
	t_mlx	mlx;

	input = read_input();
	turns = get_turns(input);
	map = ft_strdup(input);
	free(input);
	printf("%s%s", turns, map);
	if (!(nest = make_map(map)))
	{
		ft_putstr("Error\n");
		return (0);
	}
	mlx.map = nest;
	init(&mlx);
	free(map);
	free_map(&nest);
	return (0);
}
