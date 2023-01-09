/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 19:16:34 by jereverd          #+#    #+#             */
/*   Updated: 2023/01/06 12:58:45 by lorampon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	ft_check_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	ft_get_map_values(t_map *map, int fd)
{
	char	*str;

	str = get_next_line(fd);
	if (!str)
		ft_error_exit("Error: If you want to play you will need a map\n");
	map->width = (int)ft_strlen(str);
	while (*str == '\n')
	{
		free(str);
		str = get_next_line(fd);
		if (!str)
			ft_error_exit("Error: If you want to play you will need a map\n");
	}
	while (str)
	{
		if (*str == '\n')
			ft_error_exit("New line detected\n");
		ft_add_node_to_lst(&map->lst, str);
		if (map->width < (int)ft_strlen(str))
			map->width = (int)ft_strlen(str);
		map->height++;
		str = get_next_line(fd);
	}
	map->map = ft_list_to_tab(map->lst, map->width, map->height);
}

void	ft_init_parse_map_struct(t_map *m)
{
	m->map = NULL;
	m->height = 0;
	m->width = 0;
}

void	ft_init_map(t_map *map, int fd)
{
	ft_init_parse_map_struct(map);
	ft_get_map_values(map, fd);
	ft_parse_map(map);
}
