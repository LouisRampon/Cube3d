/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 10:56:31 by lorampon          #+#    #+#             */
/*   Updated: 2022/12/19 11:56:32 by lorampon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

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

t_image	ft_put_line(t_data *data, int color)
{
	
	t_vector2f	delta;
	t_vector2f	pixel;
	int			nb_pixel;
	
	delta.x = 100 * cos(data->angle);
	delta.y = 100 * sin(data->angle);
	nb_pixel = sqrt((delta.x * delta.x) + (delta.y * delta.y));
	delta.x /= nb_pixel;
	delta.y /= nb_pixel;
	pixel.x = data->pos.x;
	pixel.y = data->pos.y;
	while (nb_pixel)
	{
		my_mlx_pixel_put(&data->img, pixel.x, pixel.y, color);
		pixel.x += delta.x;
		pixel.y += delta.y;
		nb_pixel--;
	}
	return (data->img);
}

void	ft_display(t_data *data)
{
	data->img = ft_grey_backgroud(data, GREY);
	data->img = ft_put_line(data, RED);
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win_ptr, data->img.ptr, 0, 0);
}

t_data	init_data(t_data *data)
{
	t_image img;
	
	data->mlx_ptr = mlx_init();
	img.ptr = mlx_new_image(data->mlx_ptr, 1024, 512);
	img.pixels = mlx_get_data_addr(img.ptr, &img.bits_per_pixel, &img.line_size, &img.endian);
	data->img = img;
	data->pos.x = 300;
	data->pos.y = 300;
	data->angle = 0;
	data->mlx_win_ptr = mlx_new_window(data->mlx_ptr, 1024,512, "cub3d");
	ft_display(data);
	return (*data);
}

int main (int argc, char **argv)
{
	t_data data;
	
	(void)argc;
	(void)argv;
	data = init_data(&data);
	mlx_hook(data.mlx_win_ptr, 2, 0, &ft_key_hook, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}