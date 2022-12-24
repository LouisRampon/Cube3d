/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 11:11:44 by lorampon          #+#    #+#             */
/*   Updated: 2022/12/21 16:32:46 by lorampon         ###   ########.fr       */
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

# define WIDTH_WINDOW 1024
# define HEIGHT_WINDOW 256
# define CUBE_SIZE 32
# define FOV 64
# define MS 5
# define TS 0.11

# define GREY 0x808080
# define RED 0xFF0000
# define WHITE 0xFFFFFF
# define BLACK 0x000000
# define ORANGE 0xFF4500
# define ORANGE2 0xFF4900
# define ORANGE3 0xFF4700

# define DR 0.0174533

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
}	t_image;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*mlx_win_ptr;
	t_map 		*map;
	t_player	player;
	t_ray		ray;
	t_image 	img;
	t_arena		*arena;
	t_texture 	*tex;
	t_vector2f	dir;
} t_data;

//############### parsing ###############
int		ft_parsing(t_data *data, char *file_name);
int		ft_parse_line(t_texture *tx, char *str);
void	ft_init_parse_map_struct(t_map *m);
void	ft_init_map(t_map *map, int fd);
void	ft_parse_map(t_map *map);

void	ft_create_first_elem(t_lst *lst, char *str);
void	ft_add_node_to_lst(t_lst **lst, char *str);
void	ft_free_lst(t_lst *lst);
unsigned int	ft_rgb(int r, int g, int b);
t_lst	*ft_new_node(char *str);
void	ft_last_lst_elem(t_lst **ptr);


//############### utils  ################
char	**ft_split_charset(char *str, char *charset);
void	ft_free_tab(char **tab);
void	ft_error_exit(char *str);
int		ft_count_char(char *str, char c);
char	**ft_list_to_tab(t_lst *lst, int width, int height);
void	*ft_arena_alloc(t_arena *arena, size_t size);

t_data	init_data(t_data *data);
t_image	ft_put_line(t_data *data, t_vector2f end, int color);
t_image ft_draw_line(t_data *data, t_vector2f start, t_vector2f end, int color);
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

t_map	init_map(t_data *data);
void ft_2d_map(t_data *data);
t_ray draw_ray_vertical(t_data *data);
t_ray draw_ray_horizontal(t_data *data);
t_ray	farthest_ray(t_data *data, t_ray ray_v, t_ray ray_h);

#endif