/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_h.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 18:50:10 by lorampon          #+#    #+#             */
/*   Updated: 2023/01/06 12:49:06 by lorampon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_ray	ft_ray_horizontal(t_data *data, t_ray ray)
{
	if (data->ray.angle == 0)
	{
		ray.coord.x = WIDTH_WINDOW - 1;
		ray.coord.y = data->player.coord.y;
		ray.side = WEST;
		return (ray);
	}
	else
	{
		ray.coord.x = 0;
		ray.coord.y = data->player.coord.y;
		ray.side = EAST;
		return (ray);
	}
}

t_ray	draw_ray_horizontal_help(t_data *data, t_ray ray, t_vector2f offset)
{
	t_vector2d	map_pos;

	map_pos.x = (int)ray.coord.x / CUBE_SIZE;
	map_pos.y = (int)ray.coord.y / CUBE_SIZE;
	while (map_pos.x < data->map->width && map_pos.y < data->map->height
		&& map_pos.x > 0 && map_pos.y > 0)
	{
		if (data->map->map[map_pos.y][map_pos.x] == '1')
			break ;
		ray.coord.x += offset.x;
		ray.coord.y += offset.y;
		map_pos.x = (int)ray.coord.x / CUBE_SIZE;
		map_pos.y = (int)ray.coord.y / CUBE_SIZE;
	}
	if (data->ray.angle > M_PI)
		ray.side = SOUTH;
	else
		ray.side = NORTH;
	return (ray);
}

t_ray	draw_ray_horizontal(t_data *data)
{
	t_ray		ray;
	t_vector2f	offset;
	float		atan;

	atan = -1 / tan(data->ray.angle);
	ray.angle = data->ray.angle;
	if (data->ray.angle == 0 || data->ray.angle == M_PI)
		return (ft_ray_horizontal(data, ray));
	else if (data->ray.angle > M_PI)
	{
		ray.coord.y = (((int)data->player.coord.y >> 5) << 5) - 0.0001;
		ray.coord.x = (data->player.coord.y - ray.coord.y)
			* atan + data->player.coord.x;
		offset.y = -CUBE_SIZE;
		offset.x = -offset.y * atan;
	}
	if (data->ray.angle < M_PI)
	{
		ray.coord.y = (((int)data->player.coord.y >> 5) << 5) + CUBE_SIZE;
		ray.coord.x = (data->player.coord.y - ray.coord.y)
			* atan + data->player.coord.x;
		offset.y = CUBE_SIZE;
		offset.x = -offset.y * atan;
	}
	return (draw_ray_horizontal_help(data, ray, offset));
}
