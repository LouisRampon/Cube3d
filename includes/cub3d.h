/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 11:11:44 by lorampon          #+#    #+#             */
/*   Updated: 2023/01/06 13:06:32 by lorampon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/includes/libft.h"
# include "../includes/get_next_line.h"
# include "../mlx/mlx.h"
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>

enum args {space = ' ', wall = '1', floor1 = '0', p_north = 'N',\
			p_south = 'S', p_east = 'E', p_west = 'W'};

# define W 13
# define A 0
# define S 1
# define D 2
# define Q 12
# define E 14
# define ESC 53

# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3

# define WIDTH_WINDOW 960
# define HEIGHT_WINDOW 512
# define CUBE_SIZE 32
# define FOV 480
# define MS 5
# define TS 0.11

# define GREY 0x808080
# define RED 0xFF0000
# define WHITE 0xFFFFFF
# define BLACK 0x000000
# define ORANGE 0xFF4500
# define ORANGE2 0xFF4900
# define ORANGE3 0xFF4700

# define DR 0.0174533 / 8

typedef struct s_arena
{
	size_t			size;
	size_t			cursor;
	void			*data;
	struct s_arena	*next;
}t_arena;

typedef struct s_lst
{
	char			*line;
	struct s_lst	*next;
}t_lst;

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

typedef struct	s_texture
{
	char	*north;
	char	*west;
	char	*east;
	char	*south;
	int		floor[3];
	int		ceiling[3];
	int 	gnl_index;
	int 	o_index;
	int 	c_index;
	int 	f_index;
}t_texture;

typedef struct	s_ray
{
	t_vector2f	coord;
	double 		angle;
	double		dist;
	int			side;
}t_ray;

typedef struct	s_player
{
	t_vector2f	coord;
	double 		angle;
}t_player;

typedef struct	s_map
{
	char 		**map;
	int			width; //changer pour size_t
	int			height;
	t_lst 		*lst;
	t_player	player;
}t_map;

typedef struct s_image
{
	void		*ptr;
	char		*pixels;
	int			bits_per_pixel;
	int			line_size;
	int			endian;
	int 		width;
	int 		height;
}	t_image;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*mlx_win_ptr;
	t_map 		*map;
	t_player	player;
	t_ray		ray;
	t_image		img;
	t_image		texture[4];
	t_arena		*arena;
	t_texture	*tex;
	t_vector2f	dir;
	t_vector2f	ratio;
	double		lineh;
}	t_data;

//############### parsing ###############
int		ft_parsing(t_data *data, char *file_name);
int		ft_parse_line(t_texture *tx, char *str);
void	ft_init_parse_map_struct(t_map *m);

void	ft_init_map(t_map *map, int fd);
void	ft_parse_map(t_map *map);

void	ft_create_first_elem(t_lst *lst, char *str);
void	ft_add_node_to_lst(t_lst **lst, char *str);
void	ft_free_lst(t_lst *lst);
t_lst	*ft_new_node(char *str);
void	ft_last_lst_elem(t_lst **ptr);

char	**ft_split_charset(char *str, char *charset);
void	ft_free_tab(char **tab);
void	ft_error_exit(char *str);
int		ft_count_char(char *str, char c);
int		ft_only_valid_digits(char *str);
char	**ft_list_to_tab(t_lst *lst, int width, int height);

int		get_text_pixel(t_image *text, int x, int y);
int		ft_define_pxl_color(t_data *data);
void	ft_2d_map(t_data *data);
void	my_mlx_pixel_put(t_image *img, int x, int y, int color);

unsigned int ft_rgb(int r, int g, int b);
unsigned int my_mlx_pixel_get_color(t_image *data, int x, int y);

//############### raycasting  ################

t_ray	ft_ray_horizontal(t_data *data, t_ray ray);
t_ray	draw_ray_horizontal_help(t_data *data, t_ray ray, t_vector2f offset);
t_ray	draw_ray_horizontal(t_data *data);

t_ray	ft_ray_vertical(t_data *data, t_ray ray);
t_ray	draw_ray_vertical_help(t_data *data, t_ray ray, t_vector2f offset);
t_ray	draw_ray_vertical(t_data *data);

t_ray	farthest_ray(t_data *data, t_ray ray_v, t_ray ray_h);

//############### key_hook ################

void	ft_move_forward(t_data *data);
void	ft_move_backward(t_data *data);
void	ft_move_left(t_data *data);
void	ft_move_right(t_data *data);
void	ft_turn_left(t_data *data);
void	ft_turn_right(t_data *data);

int		ft_key_hook(int keycode, t_data *data);
int		check_collision(t_data *data, t_vector2f pos);
void	ft_exit(t_data *data);
int		load_texture(t_data *data, char *texture_path, int i);

//############### display & draw ################

void	ft_display(t_data *data);
double	ft_display_help(t_data *data, double camera_angle);
double	ft_texture_offset(t_data *data);
void	ft_set_ratio_x(t_data *data);
int		load_texture(t_data *data, char *texture_path, int i);

t_image	ft_put_sky(t_data *data, int color);
t_image	ft_put_ground(t_data *data, int color);
t_image	ft_draw_line(t_data *data, t_vector2f start, t_vector2f end, int color);
t_image	ft_draw_rect(t_data *data, double offsetx);
t_image	ft_draw_square(t_data *data, int color, int x, int y);

#endif