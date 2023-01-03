/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 10:56:31 by lorampon          #+#    #+#             */
/*   Updated: 2023/01/03 18:08:02 by lorampon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

unsigned int	my_mlx_pixel_get_color(t_image *data, int x, int y)
{
	char	*dst;

	dst = data->pixels + (y * data->line_size + x * (data->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

void	ft_set_ratio_x(t_data *data)
{
	if (data->ray.side == NORTH)
		data->ratio.x = (int)(data->ray.coord.x) % data->texture[NORTH].width;
	else if (data->ray.side == SOUTH)
		data->ratio.x = (int)(data->ray.coord.x) % data->texture[SOUTH].width;
	else if (data->ray.side == EAST)
		data->ratio.x = (int)(data->ray.coord.y) % data->texture[EAST].width;
	else if (data->ray.side == WEST)
		data->ratio.x = (int)(data->ray.coord.y) % data->texture[WEST].width;
}

int get_text_pixel(t_image *text, int x, int y)
{
	int color;

	
	if (x < 0 || x >= text->width)
		return (0); 
	if (y < 0 || y >= text->height)
		return (0);
	color = (*(int *)text->pixels + (y * text->line_size) + (x * text->bits_per_pixel / 8));
	return (color);
}

void	ft_define_pxl_color(t_data *data, int x, int y)
{
	if (data->ray.side == NORTH)
		my_mlx_pixel_put(&data->img, x, y,
			my_mlx_pixel_get_color(&data->texture[NORTH], data->ratio.x * data->texture[NORTH].width, data->ratio.y * data->texture[NORTH].height));
	else if (data->ray.side == SOUTH)
		my_mlx_pixel_put(&data->img, x, y,
			my_mlx_pixel_get_color(&data->texture[SOUTH], data->ratio.x * data->texture[SOUTH].width, data->ratio.y * data->texture[SOUTH].height));
	else if (data->ray.side == EAST)
		my_mlx_pixel_put(&data->img, x, y,
			my_mlx_pixel_get_color(&data->texture[EAST], data->ratio.x * data->texture[EAST].width, data->ratio.y * data->texture[EAST].height));
	else if (data->ray.side == WEST)
		my_mlx_pixel_put(&data->img, x, y,
			my_mlx_pixel_get_color(&data->texture[WEST], data->ratio.x * data->texture[WEST].width, data->ratio.y * data->texture[WEST].height));
}

t_image ft_draw_rect(t_data *data, double lineH, double offsetx)
{
	int	x;
	int	y;
	int	offsety;
	int color;
	double	step_y;
	double	text_off;

	y = 0;
	step_y = data->texture[NORTH].width / lineH;
	text_off = 0;
	if (lineH > WIDTH_WINDOW)
	{
		text_off = (lineH - WIDTH_WINDOW) / (data->texture[NORTH].width / CUBE_SIZE);
		lineH = WIDTH_WINDOW;
	}
	offsety = 256 - lineH/2;
	data->ratio.y = text_off * step_y;
	// printf("texture width = %d, ratio x = %f, ratio y =%f, step y = %f\n",data->texture[WEST].width, data->ratio.x, data->ratio.y, step_y);
	while (y < lineH)
	{
		x = 0;
		while(x < WIDTH_WINDOW / FOV)
		{
			if (data->ray.side == NORTH)
				color = my_mlx_pixel_get_color(&data->texture[NORTH], data->ratio.x, data->ratio.y);
			else if (data->ray.side == SOUTH)
				color = my_mlx_pixel_get_color(&data->texture[SOUTH], data->ratio.x, data->ratio.y);
			else if (data->ray.side == EAST)
				color = my_mlx_pixel_get_color(&data->texture[EAST], data->ratio.x, data->ratio.y);
			else if (data->ray.side == WEST)
				color = my_mlx_pixel_get_color(&data->texture[WEST], data->ratio.x, data->ratio.y);
			my_mlx_pixel_put(&data->img, offsetx + x, offsety + y, color);
			x++;
		}
		data->ratio.y += step_y;
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
	data->img = ft_put_sky(data, ft_rgb(data->tex->ceiling[0], data->tex->ceiling[1], data->tex->ceiling[2]));
	data->img = ft_put_ground(data, ft_rgb(data->tex->floor[0], data->tex->floor[1], data->tex->floor[2]));
	data->ray.angle = data->player.angle;
	data->ray.angle = data->ray.angle - ((FOV / 2) * DR);
	if (data->ray.angle >= 2 * M_PI)
		data->ray.angle -= 2 * M_PI;
	if (data->ray.angle <= 0)
		data->ray.angle += 2 * M_PI;
	//ft_2d_map(data);
	while (fov < FOV)
	{
		data->ray.angle += DR;
		if (data->ray.angle >= (2 * M_PI))
			data->ray.angle = 0;
		data->ray = farthest_ray(data, draw_ray_horizontal(data), draw_ray_vertical(data));		
		//data->img = ft_draw_line(data, data->player.coord, data->ray.coord, RED);
		camera_angle = data->player.angle - data->ray.angle;
		if (camera_angle > (2 * M_PI))
			camera_angle -= 2 * M_PI;
		if (camera_angle < 0)
			camera_angle += 2 * M_PI;
		data->ray.dist = data->ray.dist * cos(camera_angle);
		lineH = (CUBE_SIZE * HEIGHT_WINDOW) / data->ray.dist;
		ft_set_ratio_x(data);
		data->img = ft_draw_rect(data, lineH, fov * (WIDTH_WINDOW / FOV));
		fov++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win_ptr, data->img.ptr, 0, 0);
}

int load_texture(t_data *data, char *texture_path, int i)
{
	data->texture[i].ptr = mlx_xpm_file_to_image(data->mlx_ptr, texture_path, 
		&data->texture[i].width, &data->texture[i].height);
	if (data->texture[i].ptr == NULL)
		return (1);
	data->texture[i].pixels = mlx_get_data_addr(data->texture[i].ptr, 
		&data->texture[i].bits_per_pixel, &data->texture[i].line_size, &data->texture[i].endian);
	if (data->texture[i].pixels == NULL)
		return (1);
	return (0);
}

t_data	init_data(t_data *data)
{
	t_image img;

	data->mlx_ptr = mlx_init();
	img.ptr = mlx_new_image(data->mlx_ptr, WIDTH_WINDOW, HEIGHT_WINDOW);
	img.pixels = mlx_get_data_addr(img.ptr, &img.bits_per_pixel, &img.line_size, &img.endian);
	data->img = img;
	data->player.coord.x = data->map->player.coord.x * CUBE_SIZE + CUBE_SIZE / 2;
	data->player.coord.y = data->map->player.coord.y * CUBE_SIZE + CUBE_SIZE / 2;
	data->player.angle = data->map->player.angle;
	data->dir.x = cos(data->player.angle);
	data->dir.y = sin(data->player.angle);
	load_texture(data, data->tex->north, NORTH);
	load_texture(data, data->tex->south, SOUTH);
	load_texture(data, data->tex->east, EAST);
	load_texture(data, data->tex->west, WEST);
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