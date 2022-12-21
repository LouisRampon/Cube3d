/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 16:08:26 by lorampon          #+#    #+#             */
/*   Updated: 2022/06/08 16:16:24 by lorampon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_btoi(void *ptr)
{
	int			i;
	long int	exp;
	int			res;
	char		*str;

	str = ptr;
	i = 0;
	res = 0;
	exp = 2147483648;
	while (str[i])
	{
		if (str[i] == '1')
			res = exp + res;
		exp = exp / 2;
		i++;
	}
	return (res);
}
