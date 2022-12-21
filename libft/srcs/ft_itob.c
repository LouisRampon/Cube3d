/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itob.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 16:08:07 by lorampon          #+#    #+#             */
/*   Updated: 2022/06/08 16:16:10 by lorampon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_itob(int nbr)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = malloc(sizeof(char) * 33);
	if (!str)
		return (0);
	while (j < 32)
	{
		if (nbr % 2)
			str[i] = '1';
		else
			str[i] = '0';
		nbr = nbr / 2;
		i++;
		j++;
	}
	str[j] = '\0';
	ft_revstr(str);
	return (str);
}
