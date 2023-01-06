/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 16:40:16 by lorampon          #+#    #+#             */
/*   Updated: 2023/01/06 12:50:40 by lorampon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_move_backward(t_data *data)
{
	t_vector2f	temp;

	temp.x = data->player.coord.x - MS * cos(data->player.angle);
	temp.y = data->player.coord.y - MS * sin(data->player.angle);
	if (check_collision(data, temp))
		return ;
	mlx_clear_window(data->mlx_ptr, data->mlx_win_ptr);
	data->player.coord = temp;
	ft_display(data);
}

void	ft_move_left(t_data *data)
{
	t_vector2f	temp;

	temp.x = data->player.coord.x + MS * cos(data->player.angle - M_PI_2);
	temp.y = data->player.coord.y - MS * sin(data->player.angle + M_PI_2);
	if (check_collision(data, temp))
		return ;
	mlx_clear_window(data->mlx_ptr, data->mlx_win_ptr);
	data->player.coord = temp;
	ft_display(data);
}

void	ft_move_right(t_data *data)
{
	t_vector2f	temp;

	temp.x = data->player.coord.x - MS * cos(data->player.angle - M_PI_2);
	temp.y = data->player.coord.y + MS * sin(data->player.angle + M_PI_2);
	if (check_collision(data, temp))
		return ;
	mlx_clear_window(data->mlx_ptr, data->mlx_win_ptr);
	data->player.coord = temp;
	ft_display(data);
}

void	ft_turn_left(t_data *data)
{
	mlx_clear_window(data->mlx_ptr, data->mlx_win_ptr);
	data->player.angle += TS;
	if (data->player.angle >= (2 * M_PI))
		data->player.angle = 0;
	data->dir.x = cos(data->player.angle);
	data->dir.y = sin(data->player.angle);
	ft_display(data);
}

void	ft_turn_right(t_data *data)
{
	mlx_clear_window(data->mlx_ptr, data->mlx_win_ptr);
	data->player.angle -= TS;
	if (data->player.angle <= 0)
		data->player.angle = 2 * M_PI;
	data->dir.x = cos(data->player.angle);
	data->dir.y = sin(data->player.angle);
	ft_display(data);
}
