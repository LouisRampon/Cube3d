/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 10:56:31 by lorampon          #+#    #+#             */
/*   Updated: 2022/12/21 13:21:02 by lorampon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


void	ft_display(t_data *data)
{
	t_vector2f ray_h;
	t_vector2f ray_v;
	int fov;
	
	fov = 0;
	ft_2d_map(data);
	data->angle -= 30 * DR;
	while (fov < 60)
	{
		data->angle += DR;
		ray_v = draw_ray_vertical(data);
		ray_h = draw_ray_horizontal(data);
		data->img = farthest_ray(data, ray_v, ray_h);
		fov++;
	}
	data->angle -= 30 * DR;
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
	data->dir.x = cos(data->angle);
	data->dir.y = sin(data->angle);
	data->coord.x = data->pos.x / 64;
	data->coord.y = data->pos.y / 64;
	data->mlx_win_ptr = mlx_new_window(data->mlx_ptr, 1024,512, "cub3d");
	//data->map = init_map(data);
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