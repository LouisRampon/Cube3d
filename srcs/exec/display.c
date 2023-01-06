/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 18:59:42 by lorampon          #+#    #+#             */
/*   Updated: 2023/01/06 14:39:00 by lorampon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

double	ft_display_help(t_data *data, double camera_angle)
{
	data->ray.angle += DR;
	if (data->ray.angle >= (2 * M_PI))
		data->ray.angle = 0;
	data->ray = farthest_ray(data, draw_ray_horizontal(data),
			draw_ray_vertical(data));
	camera_angle = data->player.angle - data->ray.angle;
	if (camera_angle > (2 * M_PI))
		camera_angle -= 2 * M_PI;
	if (camera_angle < 0)
		camera_angle += 2 * M_PI;
	data->ray.dist = data->ray.dist * cos(camera_angle);
	data->lineh = (CUBE_SIZE * HEIGHT_WINDOW) / data->ray.dist;
	ft_set_ratio_x(data);
	return (camera_angle);
}

void	ft_display(t_data *data)
{
	int		fov;
	double	camera_angle;

	fov = 0;
	data->img = ft_put_sky(data, ft_rgb(data->tex->ceiling[0],
				data->tex->ceiling[1], data->tex->ceiling[2]));
	data->img = ft_put_ground(data, ft_rgb(data->tex->floor[0],
				data->tex->floor[1], data->tex->floor[2]));
	data->ray.angle = data->player.angle;
	data->ray.angle = data->ray.angle - ((FOV / 2) * DR);
	if (data->ray.angle > 2 * M_PI)
		data->ray.angle -= 2 * M_PI;
	if (data->ray.angle < 0)
		data->ray.angle += 2 * M_PI;
	while (fov < FOV)
	{	
		camera_angle = ft_display_help(data, camera_angle);
		data->img = ft_draw_rect(data, fov * (WIDTH_WINDOW / FOV));
		fov++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win_ptr,
		data->img.ptr, 0, 0);
}

int	load_texture(t_data *data, char *texture_path, int i)
{
	data->texture[i].ptr = mlx_xpm_file_to_image(data->mlx_ptr, texture_path,
			&data->texture[i].width, &data->texture[i].height);
	if (data->texture[i].ptr == NULL)
		return (1);
	data->texture[i].pixels = mlx_get_data_addr(data->texture[i].ptr,
			&data->texture[i].bits_per_pixel,
			&data->texture[i].line_size, &data->texture[i].endian);
	if (data->texture[i].pixels == NULL)
		return (1);
	return (0);
}

double	ft_texture_offset(t_data *data)
{
	double	offset;

	offset = 0.0;
	if (data->lineh > WIDTH_WINDOW)
	{
		if (data->ray.side == NORTH)
			offset = (data->lineh - WIDTH_WINDOW)
				/ (data->texture[NORTH].width / 32);
		else if (data->ray.side == SOUTH)
			offset = (data->lineh - WIDTH_WINDOW)
				/ (data->texture[SOUTH].width / 32);
		else if (data->ray.side == EAST)
			offset = (data->lineh - WIDTH_WINDOW)
				/ (data->texture[EAST].width / 32);
		else if (data->ray.side == WEST)
			offset = (data->lineh - WIDTH_WINDOW)
				/ (data->texture[WEST].width / 32);
		data->lineh = WIDTH_WINDOW;
	}
	else
		offset = 0;
	return (offset);
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
