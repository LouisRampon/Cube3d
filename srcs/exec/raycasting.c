/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 11:33:09 by lorampon          #+#    #+#             */
/*   Updated: 2023/01/06 12:50:10 by lorampon         ###   ########.fr       */
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

t_ray	farthest_ray(t_data *data, t_ray ray_v, t_ray ray_h)
{
	double	h;
	double	v;
	double	temp;

	temp = (data->player.coord.x - ray_v.coord.x)
		* (data->player.coord.x - ray_v.coord.x);
	temp = (data->player.coord.y - ray_v.coord.y)
		* (data->player.coord.y - ray_v.coord.y) + temp;
	v = sqrt((temp));
	temp = (data->player.coord.x - ray_h.coord.x)
		* (data->player.coord.x - ray_h.coord.x);
	temp = (data->player.coord.y - ray_h.coord.y)
		* (data->player.coord.y - ray_h.coord.y) + temp;
	h = sqrt((temp));
	if (h > v)
	{
		ray_v.dist = v;
		return (ray_v);
	}
	else
	{
		ray_h.dist = h;
		return (ray_h);
	}
}
