/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 18:54:38 by lorampon          #+#    #+#             */
/*   Updated: 2023/01/06 13:34:17 by lorampon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	ft_exit(t_data *data)
{
	(void)data;
	exit(0);
}

int	check_collision(t_data *data, double angle)
{
	t_ray		temp;

	data->ray.angle = angle;
	temp = farthest_ray(data, draw_ray_horizontal(data),
			draw_ray_vertical(data));
	if (temp.dist < MS * 3)
		return (1);
	else
		return (0);
}

int	ft_key_hook(int keycode, t_data *data)
{
	if (keycode == W)
		ft_move_forward(data);
	else if (keycode == A)
		ft_move_left(data);
	else if (keycode == D)
		ft_move_right(data);
	else if (keycode == S)
		ft_move_backward(data);
	else if (keycode == Q)
		ft_turn_left(data);
	else if (keycode == E)
		ft_turn_right(data);
	else if (keycode == ESC || keycode == 17)
		ft_exit(data);
	return (0);
}

void	ft_move_forward(t_data *data)
{
	t_vector2f	temp;

	temp.x = data->player.coord.x + MS * cos(data->player.angle);
	temp.y = data->player.coord.y + MS * sin(data->player.angle);
	if (check_collision(data, data->player.angle))
		return ;
	mlx_clear_window(data->mlx_ptr, data->mlx_win_ptr);
	data->player.coord = temp;
	ft_display(data);
}
