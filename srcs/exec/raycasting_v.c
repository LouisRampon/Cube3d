/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_v.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 18:51:55 by lorampon          #+#    #+#             */
/*   Updated: 2023/01/06 15:28:19 by lorampon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_ray	ft_ray_vertical(t_data *data, t_ray ray)
{
	if (data->ray.angle == M_PI_2)
	{
		ray.coord.y = 0;
		ray.coord.x = data->player.coord.x;
		ray.side = NORTH;
		return (ray);
	}
	else
	{
		ray.coord.y = 0;
		ray.coord.x = data->player.coord.x;
		ray.side = SOUTH;
		return (ray);
	}
}

t_ray	draw_ray_vertical_help(t_data *data, t_ray ray, t_vector2f offset)
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
	if (data->ray.angle < M_PI_2 || data->ray.angle > M_PI_2 * 3)
		ray.side = WEST;
	else
		ray.side = EAST;
	return (ray);
}

t_ray	draw_ray_vertical(t_data *data)
{
	t_ray		ray;
	t_vector2f	offset;
	float		ntan;

	ntan = -tan(data->ray.angle);
	ray.angle = data->ray.angle;
	if (data->ray.angle == M_PI_2 || data->ray.angle == M_PI_2 * 3)
		return (ft_ray_vertical(data, ray));
	else if (data->ray.angle > M_PI_2 && data->ray.angle < M_PI_2 * 3)
	{
		ray.coord.x = (((int)data->player.coord.x >> 6) << 6) - 0.0001;
		ray.coord.y = (data->player.coord.x - ray.coord.x)
			* ntan + data->player.coord.y;
		offset.x = -CUBE_SIZE;
		offset.y = -offset.x * ntan;
	}
	else
	{
		ray.coord.x = (((int)data->player.coord.x >> 6) << 6) + CUBE_SIZE;
		ray.coord.y = (data->player.coord.x - ray.coord.x)
			* ntan + data->player.coord.y;
		offset.x = CUBE_SIZE;
		offset.y = -offset.x * ntan;
	}
	return (draw_ray_vertical_help(data, ray, offset));
}
