/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 10:56:31 by lorampon          #+#    #+#             */
/*   Updated: 2022/12/21 16:19:42 by lorampon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_image ft_draw_rect(t_data *data, double lineH, double offsetx)
{
	int	x;
	int	y;
	int	offsety;

	y = 0;
	offsety = 128 - lineH/2;
	while (y < lineH)
	{
		x = 0;
		while(x < 8)
		{
			my_mlx_pixel_put(&data->img, offsetx + x, offsety + y, RED);
			x++;
		}
		y++;
	}
	return (data->img);
}

void	ft_display(t_data *data)
{
	int fov;
	double lineH;
	double camera_angle;
	
	fov = 0;
	data->img = ft_grey_backgroud(data, GREY);
	ft_2d_map(data);
	data->ray = data->player;
	data->ray.angle = data->ray.angle - ((FOV / 2) * DR);
	if (data->ray.angle >= 2 * M_PI)
		data->ray.angle -= 2 * M_PI;
	if (data->ray.angle <= 0)
		data->ray.angle += 2 * M_PI;
	while (fov < FOV)
	{
		printf("rayon %d : angle = %f\n", fov, data->ray.angle);
		data->ray.angle += DR;
		if (data->ray.angle >= (2 * M_PI))
			data->ray.angle = 0;
		data->ray.coord = farthest_ray(data, draw_ray_horizontal(data), draw_ray_vertical(data));		
		data->img = ft_draw_line(data, data->player.coord, data->ray.coord, RED);
		camera_angle = data->player.angle - data->ray.angle;
		if (camera_angle > (2 * M_PI))
			camera_angle -= 2 * M_PI;
		if (camera_angle < 0)
			camera_angle += 2 * M_PI;
		data->ray.dist = data->ray.dist * cos(camera_angle);
		lineH = (CUBE_SIZE * 512) / data->ray.dist;
		if (lineH > 512)
			lineH = 512;
		data->img = ft_draw_rect(data, lineH, 512 + fov * 8);
		fov++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win_ptr, data->img.ptr, 0, 0);
}

t_data	init_data(t_data *data)
{
	t_image img;
	
	data->mlx_ptr = mlx_init();
	img.ptr = mlx_new_image(data->mlx_ptr, WIDTH_WINDOW * 2, HEIGHT_WINDOW);
	img.pixels = mlx_get_data_addr(img.ptr, &img.bits_per_pixel, &img.line_size, &img.endian);
	data->img = img;
	data->player.coord.x = data->map->player.coord.x * CUBE_SIZE + CUBE_SIZE / 2;
	data->player.coord.y = data->map->player.coord.y * CUBE_SIZE + CUBE_SIZE / 2;
	data->player.angle = data->map->player.angle;
	data->dir.x = cos(data->player.angle);
	data->dir.y = sin(data->player.angle);
	// data->coord.x = (int)data->pos.x / CUBE_SIZE;
	// data->coord.y = (int)data->pos.y / CUBE_SIZE;
	data->mlx_win_ptr = mlx_new_window(data->mlx_ptr, WIDTH_WINDOW, HEIGHT_WINDOW, "cub3d");
	ft_display(data);
	return (*data);
}

int main (int ac, char **av)
{
	t_texture t;
	t_map map;
	t_arena a;
	t_data data;

	if (ac != 2)
		return (0);
	data.tex = &t;
	data.map = &map;
	data.arena = &a;
	data.map->lst = NULL;
	ft_parsing(&data, av[1]);
	data = init_data(&data);
	mlx_hook(data.mlx_win_ptr, 2, 0, &ft_key_hook, &data);
	mlx_loop(data.mlx_ptr);
	ft_free_tab(data.map->map);
	ft_free_lst(data.map->lst);
	return (0);
}