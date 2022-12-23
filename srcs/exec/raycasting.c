/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 11:33:09 by lorampon          #+#    #+#             */
/*   Updated: 2022/12/21 16:18:38 by lorampon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_image	ft_put_line(t_data *data, t_vector2f end, int color)
{
	t_vector2f	delta;
	t_vector2f	pixel;
	int			nb_pixel;
	
	delta.x = end.x - data->player.coord.x;
	delta.y = end.y - data->player.coord.y;
	nb_pixel = sqrt((delta.x * delta.x) + (delta.y * delta.y));
	delta.x /= nb_pixel;
	delta.y /= nb_pixel;
	pixel.x = data->player.coord.x;
	pixel.y = data->player.coord.y;
	while (nb_pixel)
	{
		my_mlx_pixel_put(&data->img, pixel.x, pixel.y, color);
		pixel.x += delta.x;
		pixel.y += delta.y;
		nb_pixel--;
	}
	return (data->img);
}

t_vector2f draw_ray_vertical(t_data *data)
{
	t_vector2f ray;
	t_vector2f offset;
	t_vector2d map_pos;
	float ntan;

	ntan = -tan(data->ray.angle);
	if (data->ray.angle == M_PI_2)
	{
		ray.y = 0;
		ray.x = data->player.coord.x;
		return (ray);
	}
	else if (data->ray.angle == M_PI_2 * 3)
	{
		ray.y = 0;
		ray.x = data->player.coord.x;	
		return (ray);	
	}
	else if (data->ray.angle > M_PI_2 && data->ray.angle < M_PI_2 * 3)
	{
		ray.x = (((int)data->player.coord.x>>5)<<5)-0.0001;
		ray.y = (data->player.coord.x - ray.x) * ntan + data->player.coord.y;
		offset.x = -CUBE_SIZE;
		offset.y = -offset.x * ntan;
	}
	else if (data->ray.angle < M_PI_2 || data->ray.angle > M_PI_2 * 3)
	{
		ray.x = (((int)data->player.coord.x>>5)<<5)+ CUBE_SIZE;
		ray.y = (data->player.coord.x - ray.x) * ntan + data->player.coord.y;
		offset.x = CUBE_SIZE;
		offset.y = -offset.x * ntan;	
	}
	map_pos.x = (int)ray.x / CUBE_SIZE;
	map_pos.y = (int)ray.y / CUBE_SIZE;
	while (map_pos.x < data->map->width && map_pos.y < data->map->height
			&& map_pos.x > 0 && map_pos.y > 0)
	{
		if (data->map->map[map_pos.y][map_pos.x] == '1')
			return (ray);
		ray.x += offset.x;
		ray.y += offset.y;
		map_pos.x = (int)ray.x / CUBE_SIZE;
		map_pos.y = (int)ray.y / CUBE_SIZE;
	}
	return (ray);
}

t_vector2f draw_ray_horizontal(t_data *data)
{
	t_vector2f ray;
	t_vector2f offset;
	t_vector2d map_pos;
	float atan;

	atan = -1/tan(data->ray.angle);
	if (data->ray.angle == 0)
	{
		ray.x = WIDTH_WINDOW - 1;
		ray.y = data->player.coord.y;
		return (ray);
	}
	else if (data->ray.angle == M_PI)
	{
		ray.x = 0;
		ray.y = data->player.coord.y;	
		return (ray);	
	}
	else if (data->ray.angle > M_PI)
	{
		ray.y = (((int)data->player.coord.y>>5)<<5)-0.0001;
		ray.x = (data->player.coord.y - ray.y) * atan + data->player.coord.x;
		offset.y = -CUBE_SIZE;
		offset.x = -offset.y * atan;
	}
	else if (data->ray.angle < M_PI)
	{
		ray.y = (((int)data->player.coord.y>>5)<<5)+ CUBE_SIZE;
		ray.x = (data->player.coord.y - ray.y) * atan + data->player.coord.x;
		offset.y = CUBE_SIZE;
		offset.x = -offset.y * atan;	
	}
	map_pos.x = (int)ray.x / CUBE_SIZE;
	map_pos.y = (int)ray.y / CUBE_SIZE;
	while (map_pos.x < data->map->width && map_pos.y < data->map->height 
			&& map_pos.x > 0 && map_pos.y > 0)
	{
		if (data->map->map[map_pos.y][map_pos.x] == '1')
			return (ray);
		ray.x += offset.x;
		ray.y += offset.y;
		map_pos.x = (int)ray.x / CUBE_SIZE;
		map_pos.y = (int)ray.y / CUBE_SIZE;
	}
	return (ray);
}

t_vector2f	farthest_ray(t_data *data, t_vector2f ray_v, t_vector2f ray_h)
{
	double h;
	double v;
	double temp;

	temp = (data->player.coord.x - ray_v.x) * (data->player.coord.x - ray_v.x);	
	temp = (data->player.coord.y - ray_v.y) * (data->player.coord.y - ray_v.y) + temp;
	v = sqrt((temp));
	temp = (data->player.coord.x - ray_h.x) * (data->player.coord.x - ray_h.x);	
	temp = (data->player.coord.y - ray_h.y) * (data->player.coord.y - ray_h.y) + temp;
	h = sqrt((temp));
	//printf("x vert = %f, y vert = %f\n x hoz = %f, y hoz = %f\n h = %f, v = %f\n", ray_v.x, ray_v.y, ray_h.x, ray_h.y, h, v);
	if (h > v)
	{
		data->ray.dist = v;
		return (ray_v);
	}
	else
	{
		data->ray.dist = h;
		return (ray_h);
	}
}