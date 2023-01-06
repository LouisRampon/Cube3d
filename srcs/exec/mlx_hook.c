/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 18:54:38 by lorampon          #+#    #+#             */
/*   Updated: 2023/01/06 12:51:06 by lorampon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_exit(t_data *data)
{
	(void)data;
	exit(0);
}

int	check_collision(t_data *data, t_vector2f pos)
{
	t_vector2d	temp;

	temp.x = (int)pos.x / CUBE_SIZE;
	temp.y = (int)pos.y / CUBE_SIZE;
	if (data->map->map[temp.y][temp.x] == '1')
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
	else if (keycode == ESC)
		ft_exit(data);
	return (0);
}

void	ft_move_forward(t_data *data)
{
	t_vector2f	temp;

	temp.x = data->player.coord.x + MS * cos(data->player.angle);
	temp.y = data->player.coord.y + MS * sin(data->player.angle);
	if (check_collision(data, temp))
		return ;
	mlx_clear_window(data->mlx_ptr, data->mlx_win_ptr);
	data->player.coord = temp;
	ft_display(data);
}
