/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 13:46:29 by lorampon          #+#    #+#             */
/*   Updated: 2022/12/19 15:50:43 by lorampon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= WIDTH_WINDOW || y >= HEIGHT_WINDOW)
		return ;
	dst = img->pixels + (y * img->line_size + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
 
t_image ft_grey_backgroud(t_data *data, int color)
{
	int	x;
	int	y;
	
	x = 0;
	y = 0;
	while (y < 512)
	{
		while(x < 1024)
		{
			my_mlx_pixel_put(&data->img, x, y, color);
			x++;
		}
		x = 0;
		y++;
	}
	return (data->img);
}

t_image	ft_draw_square(t_data *data, int color, int x, int y)
{
	int i;
	int j;
	
	j = 0;
	while (j < 64)
	{
		i = 0;
		while (i < 64)
		{	
			if (i == 0 || j == 0 || i == 63 || j == 63)
				my_mlx_pixel_put(&data->img, x * 64 + i, y * 64 + j, BLACK);
			else
				my_mlx_pixel_put(&data->img, x * 64 + i, y * 64 + j, color);
			i++;
		}
		j++;
	}
	return(data->img);
}

void ft_2d_map(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->map.height)
	{
		x = 0;
		while (x < data->map.width)
		{	
			if (data->map.map[y][x] == '1')
				data->img = ft_draw_square(data, WHITE, x ,y);
			else if (data->map.map[y][x] == '0')
				data->img = ft_draw_square(data, GREY, x ,y);
			x++;
		}
		y++;
	}
}

t_map	init_map(t_data *data)
{
	t_map map;
	char **map1;
	(void)data;
	int i;
	int j;
	j = 0;
	map1 = malloc(sizeof(map1) * 8 + 1);
	while (j < 8)
	{
		i = 0;
		map1[j] = malloc(sizeof(char) * 16 + 1);
		while (i < 16)
		{
			map1[j][i] = '0';
			i++;
		}
		j++;
	}
	map1[5][7] = '1';
	map.map = map1;
	map.height = 8;
	map.width = 16;
	return (map);
}
