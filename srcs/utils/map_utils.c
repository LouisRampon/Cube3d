/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 13:46:29 by lorampon          #+#    #+#             */
/*   Updated: 2022/12/21 11:52:34 by lorampon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= WIDTH_WINDOW|| y >= HEIGHT_WINDOW)
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
	while (y < HEIGHT_WINDOW)
	{
		while(x < WIDTH_WINDOW)
		{
			my_mlx_pixel_put(&data->img, x, y, color);
			x++;
		}
		x = 0;
		y++;
	}
	return (data->img);
}

t_image ft_draw_line(t_data *data, t_vector2f start, t_vector2f end, int color)
{
	t_vector2f	delta;
	t_vector2f	pixel;
	int			nb_pixel;
	
	delta.x = end.x - start.x;
	delta.y = end.y - start.y;
	nb_pixel = sqrt((delta.x * delta.x) + (delta.y * delta.y));
	delta.x /= nb_pixel;
	delta.y /= nb_pixel;
	pixel.x = start.x;
	pixel.y = start.y;
	while (nb_pixel)
	{
		my_mlx_pixel_put(&data->img, pixel.x, pixel.y, color);
		pixel.x += delta.x;
		pixel.y += delta.y;
		nb_pixel--;
	}
	return (data->img);
}

t_image	ft_draw_square(t_data *data, int color, int x, int y)
{
	int i;
	int j;
	
	j = 0;
	while (j < CUBE_SIZE)
	{
		i = 0;
		while (i < CUBE_SIZE)
		{	
			if (i == 0 || j == 0 || i == CUBE_SIZE - 1 || j == CUBE_SIZE - 1)
				my_mlx_pixel_put(&data->img, x * CUBE_SIZE + i, y * CUBE_SIZE + j, BLACK);
			else
				my_mlx_pixel_put(&data->img, x * CUBE_SIZE + i, y * CUBE_SIZE + j, color);
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
	while (y < data->map->height)
	{
		x = 0;
		while (x < data->map->width)
		{	
			if (data->map->map[y][x] == '1')
				data->img = ft_draw_square(data, WHITE, x ,y);
			else if (data->map->map[y][x] == '0')
				data->img = ft_draw_square(data, GREY, x ,y);
			x++;
		}
		y++;
	}
}

// t_map	*init_map(t_data *data)
// {
// 	t_map map;
// 	char **map1;
// 	(void)data;
// 	int i;
// 	int j;
// 	j = 0;
// 	map1 = malloc(sizeof(map1) * 8 + 1);
// 	while (j < 8)
// 	{
// 		i = 0;
// 		map1[j] = malloc(sizeof(char) * 16 + 1);
// 		while (i < 16)
// 		{
// 			map1[j][i] = '0';
// 			i++;
// 		}
// 		j++;
// 	}
// 	map1[5][7] = '1';
// 	map.map = map1;
// 	map.height = 8;
// 	map.width = 16;
// 	return (*map);
// }
