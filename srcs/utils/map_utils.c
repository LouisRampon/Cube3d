/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 13:46:29 by lorampon          #+#    #+#             */
/*   Updated: 2023/01/06 12:41:17 by lorampon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= WIDTH_WINDOW || y >= HEIGHT_WINDOW)
		return ;
	dst = img->pixels + (y * img->line_size + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	ft_2d_map(t_data *data)
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
				data->img = ft_draw_square(data, WHITE, x, y);
			else if (data->map->map[y][x] == '0')
				data->img = ft_draw_square(data, GREY, x, y);
			x++;
		}
		y++;
	}
}

unsigned int	my_mlx_pixel_get_color(t_image *data, int x, int y)
{
	char	*dst;

	dst = data->pixels + (y * data->line_size
			+ x * (data->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

int	get_text_pixel(t_image *text, int x, int y)
{
	int	color;

	if (x < 0 || x >= text->width)
		return (0);
	if (y < 0 || y >= text->height)
		return (0);
	color = (*(int *)text->pixels + (y * text->line_size)
			+ (x * text->bits_per_pixel / 8));
	return (color);
}

int	ft_define_pxl_color(t_data *data)
{
	int	color;

	if (data->ray.side == NORTH)
		color = my_mlx_pixel_get_color(&data->texture[NORTH],
				data->ratio.x, data->ratio.y);
	else if (data->ray.side == SOUTH)
		color = my_mlx_pixel_get_color(&data->texture[SOUTH],
				data->ratio.x, data->ratio.y);
	else if (data->ray.side == EAST)
		color = my_mlx_pixel_get_color(&data->texture[EAST],
				data->ratio.x, data->ratio.y);
	else
		color = my_mlx_pixel_get_color(&data->texture[WEST],
				data->ratio.x, data->ratio.y);
	return (color);
}
