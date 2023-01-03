/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 19:16:53 by jereverd          #+#    #+#             */
/*   Updated: 2023/01/03 13:35:33 by lorampon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	ft_open_file(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Could not open file\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

void	ft_check_extension(char *file_name)
{
	char	*str;

	str = ft_strrchr(file_name, '.');
	if (!str || ft_strcmp(str, ".cub") != 0)
	{
		ft_putstr_fd(".cub file name extension expected\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}

void	ft_init_txt_and_colors(t_texture *tx, int fd)
{
	char	*line;
	char	*temp;

	line = get_next_line(fd);
	temp = NULL;
	while (line)
	{
		temp = ft_substr(line, 0, ft_strlen(line) - 1);
		ft_parse_line(tx, temp);
		free(line);
		free(temp);
		tx->gnl_index += 1;
		if (tx->f_index + tx->c_index + tx->o_index == 6)
			break ;
		line = get_next_line(fd);
	}
	if (!tx->north || !tx->south || !tx->east || !tx->west || \
		!tx->c_index || !tx->f_index)
		ft_error_exit("Missing options\n");
}

void	ft_init_parse_options_struct(t_texture *tx)
{
	tx->west = NULL;
	tx->east = NULL;
	tx->north = NULL;
	tx->south = NULL;
	tx->o_index = 0;
	tx->c_index = 0;
	tx->f_index = 0;
	tx->gnl_index = 0;
}

int	ft_parsing(t_data *data, char *file_name)
{
	int	fd;

	ft_check_extension(file_name);
	fd = ft_open_file(file_name);
	ft_init_parse_options_struct(data->tex);
	ft_init_txt_and_colors(data->tex, fd);
	ft_init_map(data->map, fd);
	close(fd);
	return (0);
}
