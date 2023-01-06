/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_option_help.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 13:00:02 by lorampon          #+#    #+#             */
/*   Updated: 2023/01/06 13:00:19 by lorampon         ###   ########.fr       */
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

unsigned int	ft_rgb(int r, int g, int b)
{
	return ((r * 256 * 256) + (g * 256) + b);
}