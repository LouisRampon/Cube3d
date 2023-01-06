/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 10:56:31 by lorampon          #+#    #+#             */
/*   Updated: 2023/01/06 13:25:20 by lorampon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_data	init_data(t_data *data)
{
	t_image	img;

	data->mlx_ptr = mlx_init();
	img.ptr = mlx_new_image(data->mlx_ptr, WIDTH_WINDOW, HEIGHT_WINDOW);
	img.pixels = mlx_get_data_addr(img.ptr, &img.bits_per_pixel,
			&img.line_size, &img.endian);
	data->img = img;
	data->player.coord.x = data->map->player.coord.x
		* CUBE_SIZE + CUBE_SIZE / 2;
	data->player.coord.y = data->map->player.coord.y
		* CUBE_SIZE + CUBE_SIZE / 2;
	data->player.angle = data->map->player.angle;
	data->dir.x = cos(data->player.angle);
	data->dir.y = sin(data->player.angle);
	load_texture(data, data->tex->north, NORTH);
	load_texture(data, data->tex->south, SOUTH);
	load_texture(data, data->tex->east, EAST);
	load_texture(data, data->tex->west, WEST);
	data->mlx_win_ptr = mlx_new_window(data->mlx_ptr,
			WIDTH_WINDOW, HEIGHT_WINDOW, "cub3d");
	ft_display(data);
	return (*data);
}

int	main(int ac, char **av)
{
	t_texture	t;
	t_map		map;
	t_arena		a;
	t_data		data;

	if (ac != 2)
	{
		printf("Invalid arguments\n");
		return (0);
	}
	data.tex = &t;
	data.map = &map;
	data.arena = &a;
	data.map->lst = NULL;
	ft_parsing(&data, av[1]);
	data = init_data(&data);
	mlx_hook(data.mlx_win_ptr, 2, 0, &ft_key_hook, &data);
	mlx_hook(data.mlx_win_ptr, 17, 0, *ft_exit, &data);
	mlx_loop(data.mlx_ptr);
	ft_free_tab(data.map->map);
	ft_free_lst(data.map->lst);
	return (0);
}
