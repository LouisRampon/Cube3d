/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_options.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jereverd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 19:16:49 by jereverd          #+#    #+#             */
/*   Updated: 2022/12/19 19:16:50 by jereverd         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	ft_only_valid_digits(char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	if (ft_atoi(str) > 255)
		return (0);
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 1)
			count++;
		i++;
	}
	if (i == count)
		return (1);
	return (0);
}

//void	ft_convert_rgb(t_texture *tx)
//{
//	return ()
//}

void	ft_parse_rgb(t_texture *tx, char *param, int flag)
{
	char	**tab;

	if (ft_count_char(param, ',') > 2)
		ft_error_exit("error\n");
	tab = ft_split(param, ',');
	if (!tab)
		ft_error_exit("Split failed\n");
	if (!tab[0] || !tab[1] || !tab[2])
		ft_error_exit("Format error: expected 3 numbers in RGB\n");
	if (!ft_only_valid_digits(tab[0]) || \
		!ft_only_valid_digits(tab[1]) || \
		!ft_only_valid_digits(tab[2]))
		ft_error_exit("Format error: expected valid digits in RGB\n");
	if (flag == 1)
	{
		tx->ceiling[0] = (int)ft_atoi(tab[0]);
		tx->ceiling[1] = (int)ft_atoi(tab[1]);
		tx->ceiling[2] = (int)ft_atoi(tab[2]);
		tx->c_index = 1;
	}
	else
	{
		tx->floor[0] = (int)ft_atoi(tab[0]);
		tx->floor[1] = (int)ft_atoi(tab[1]);
		tx->floor[2] = (int)ft_atoi(tab[2]);
		tx->f_index = 1;
	}
	ft_free_tab(tab);
}

char	*ft_check_access(t_texture *tx, char *param, int fd)
{
	if (fd == -1)
		ft_error_exit("Path is not valid\n");
	tx->o_index += 1;
	return (param);
}

void	ft_if_else_if(t_texture *tx, char *identifier, char *param)
{
	int	fd;

	fd = open(param, F_OK | X_OK);
	if (ft_strcmp(identifier, "NO") == 0)
		tx->north = ft_check_access(tx, param, fd);
	else if (ft_strcmp(identifier, "SO") == 0)
		tx->south = ft_check_access(tx, param, fd);
	else if (ft_strcmp(identifier, "EA") == 0)
		tx->east = ft_check_access(tx, param, fd);
	else if (ft_strcmp(identifier, "WE") == 0)
		tx->west = ft_check_access(tx, param, fd);
	else if (ft_strcmp(identifier, "C") == 0)
		ft_parse_rgb(tx, param, 1);
	else if (ft_strcmp(identifier, "F") == 0)
		ft_parse_rgb(tx, param, 2);
	else
		ft_error_exit("Format error\n");
	close(fd);
}

int	ft_parse_line(t_texture *tx, char *str)
{
	char	**tab;
	char	*identifier;
	char	*param;

	if (!*str)
		return (0);
	param = NULL;
	tab = ft_split_charset(str, " \t");
	if (!tab)
		ft_error_exit("Split failed\n");
	identifier = tab[0];
	if (!identifier)
		ft_error_exit("Identifier is null\n");
	if (tab[1])
		param = ft_substr(tab[1], 0, ft_strlen(tab[1]));
	if (!param)
		ft_error_exit("Error\n");
	ft_if_else_if(tx, identifier, param);
	free(param);
	ft_free_tab(tab);
	return (1);
}
