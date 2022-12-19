/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 11:11:44 by lorampon          #+#    #+#             */
/*   Updated: 2022/12/12 17:21:15 by lorampon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
# include "../mlx/mlx.h"

# define W 13
# define A 0
# define S 1
# define D 2
# define Q 12
# define E 14
# define ESC 53

# define GREY 0x808080
# define RED 0xFF0000
typedef struct s_vector2d
{
	int	x;
	int	y;
}	t_vector2d;

typedef struct s_vector2f
{
	double x;
	double y;
}	t_vector2f;
typedef struct s_image
{
	void		*ptr;
	char		*pixels;
	int			bits_per_pixel;
	int			line_size;
	int			endian;
}	t_image;
typedef struct s_data
{
	void	*mlx_ptr;
	void	*mlx_win_ptr;
	t_vector2f	pos;
	double		angle;
	t_image 	img;
	
} t_data;

t_data	init_data(t_data *data);
t_image	ft_put_line(t_data *data, int color);
t_image ft_grey_backgroud(t_data *data, int color);
void	my_mlx_pixel_put(t_image *img, int x, int y, int color);

void	ft_move_forward(t_data *data);
void	ft_move_backward(t_data *data);
void	ft_move_left(t_data *data);
void	ft_move_right(t_data *data);
void	ft_turn_left(t_data *data);
void	ft_turn_right(t_data *data);
int	ft_key_hook(int keycode, t_data *data);
void	ft_display(t_data *data);

#endif