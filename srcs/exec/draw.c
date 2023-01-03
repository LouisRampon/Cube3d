/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 18:58:38 by lorampon          #+#    #+#             */
/*   Updated: 2023/01/03 19:07:44 by lorampon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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

t_image ft_put_sky(t_data *data, int color)
{
	int	x;
	int	y;
	
	x = 0;
	y = 0;
	while (y < HEIGHT_WINDOW / 2)
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

t_image ft_put_ground(t_data *data, int color)
{
	int	x;
	int	y;
	
	x = 0;
	y = HEIGHT_WINDOW / 2;
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

t_image ft_draw_rect(t_data *data, double offsetx)
{
	int	x;
	int	y;
	int	offsety;
	double	step_y;

	y = 0;
	step_y = data->texture[NORTH].width / data->lineH;
	data->ratio.y = ft_texture_offset(data) * step_y;
	offsety = 256 - data->lineH/2;
	while (y < data->lineH)
	{
		x = 0;
		while(x < WIDTH_WINDOW / FOV)
		{
			my_mlx_pixel_put(&data->img, offsetx + x, offsety + y, ft_define_pxl_color(data));
			x++;
		}
		data->ratio.y += step_y;
		y++;
	}
	return (data->img);
}