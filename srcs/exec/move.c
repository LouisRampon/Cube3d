/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 16:40:16 by lorampon          #+#    #+#             */
/*   Updated: 2022/12/19 17:11:06 by lorampon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/cub3d.h"

void	ft_move_forward(t_data *data)
{
	mlx_clear_window(data->mlx_ptr, data->mlx_win_ptr);
	data->pos.x += cos(data->angle);
	data->pos.y += sin(data->angle);
	ft_display(data);
}

void	ft_move_backward(t_data *data)
{
	mlx_clear_window(data->mlx_ptr, data->mlx_win_ptr);
	data->pos.x -= cos(data->angle);
	data->pos.y -= sin(data->angle);
	ft_display(data);
}

void	ft_move_left(t_data *data)
{
	mlx_clear_window(data->mlx_ptr, data->mlx_win_ptr);
	ft_display(data);
}

void	ft_move_right(t_data *data)
{
	mlx_clear_window(data->mlx_ptr, data->mlx_win_ptr);
	ft_display(data);
}

void	ft_turn_left(t_data *data)
{
	mlx_clear_window(data->mlx_ptr, data->mlx_win_ptr);
	data->angle += 0.05;
	if (data->angle > (2 * M_PI - 0.05))
		data->angle = 0.05;
	data->dir.x = cos(data->angle);
	data->dir.y = sin(data->angle);
	ft_display(data);
}

void	ft_turn_right(t_data *data)
{
	mlx_clear_window(data->mlx_ptr, data->mlx_win_ptr);
	data->angle -= 0.05;
	if (data->angle < 0)
		data->angle = 2 * M_PI - 0.05;
	data->dir.x = cos(data->angle);
	data->dir.y = sin(data->angle);
	ft_display(data);
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
	return (0);
}
