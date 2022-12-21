/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 19:16:43 by jereverd          #+#    #+#             */
/*   Updated: 2022/12/21 11:49:26 by lorampon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	ft_check_border(char **map)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (map[i])
	{
		if (map[i][0] == space || map[i][0] == wall)
			count++;
		i++;
	}
	if (count == i)
		return (1);
	return (0);
}

int	ft_check_map_char(const char *map, int has_player)
{
	char	*accepted_char;
	char	*player_char;

	accepted_char = " 01";
	player_char = "NEWS";
	if (!ft_strchr(accepted_char, *map))
	{
		if (!ft_strchr(player_char, *map))
			ft_error_exit("Error: wrong char in map\n");
		if (has_player)
			ft_error_exit("Error: only one player expected in map\n");
		return (1);
	}
	return (0);
}

void	ft_check_if_map_closed(char **map, int i, int j)
{
	if (map[i][j] == floor1 || map[i][j] == 'N' || \
		map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W')
	{
		if ((map[i][j + 1] && map[i][j + 1] == space) || \
			(map[i][j - 1] && map[i][j - 1] == space) || \
			(map[i + 1][j] && map[i + 1][j] == space) || \
			(map[i - 1][j] && map[i - 1][j] == space))
		{
			ft_error_exit("Map is not closed\n");
		}
	}
}

void	ft_parse_map(char **map)
{
	int		has_player;
	int		i;
	int		j;

	i = 0;
	has_player = 0;
	if (ft_check_border(map) == 0)
		ft_error_exit("Map is not closed\n");
	while (map[i])
	{
		j = 1;
		while (map[i][j])
		{
			if (ft_check_map_char(&map[i][j], has_player) != 0)
				has_player = 1;
			ft_check_if_map_closed(map, i, j);
			j++;
		}
		i++;
	}
	if (!has_player)
		ft_error_exit("Error: need one player in map\n");
}
