/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 11:50:33 by lorampon          #+#    #+#             */
/*   Updated: 2022/06/03 15:52:40 by lorampon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

long	ft_pos(int n)
{
	long	nb;

	nb = n;
	if (nb < 0)
		nb = -nb;
	return (nb);
}

int	ft_size(long nb)
{
	int	i;

	i = 0;
	if (nb < 0)
		i++;
	while (nb > 0)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

char	*ft_nzero(void)
{
	char	*str;

	str = malloc(sizeof(*str) * 2);
	if (!str)
		return (0);
	str[0] = '0';
	str[1] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{	
	char	*str;
	int		i;
	long	nb;

	nb = ft_pos(n);
	i = ft_size(nb);
	i = i + (n < 0);
	if (n == 0)
		return (ft_nzero());
	str = malloc(sizeof(*str) * (i + 1));
	if (!str)
		return (0);
	str[i] = '\0';
	nb = ft_pos(n);
	while (nb > 0)
	{
		i--;
		str[i] = nb % 10 + '0';
		nb /= 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
