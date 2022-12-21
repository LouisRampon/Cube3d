/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 16:37:34 by lorampon          #+#    #+#             */
/*   Updated: 2022/05/03 13:15:45 by lorampon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_putnbr_hexa_low(unsigned int nb)
{
	int	i;

	i = 0;
	if (nb == 0)
		i++;
	ft_putnbr_base(nb, "0123456789abcdef");
	while (nb > 0)
	{
		nb /= 16;
		i++;
	}
	return (i - 1);
}

int	ft_putnbr_hexa_up(unsigned int nb)
{
	int	i;

	i = 0;
	if (nb == 0)
		i++;
	ft_putnbr_base(nb, "0123456789ABCDEF");
	while (nb > 0)
	{
		nb /= 16;
		i++;
	}
	return (i - 1);
}

int	ft_ptrhexa(void *ptr)
{
	int						i;
	unsigned long long int	s;

	i = 0;
	s = (unsigned long long int)ptr;
	ft_putstr("0x");
	ft_putnbr_base(s, "0123456789abcdef");
	if (!s)
		return (2);
	while (s > 0)
	{
		s /= 16;
		i++;
	}
	return (i + 1);
}

int	ft_putnbr(int nbr)
{
	int					i;
	unsigned long long	nb;

	i = 0;
	if (nbr < 0)
	{
		i++;
		write(1, "-", 1);
		nb = nbr;
		nb = -nb;
	}
	else
		nb = nbr;
	ft_putnbr_base(nb, "0123456789");
	if (nb == 0)
		i++;
	while (nb > 0)
	{
		nb /= 10;
		i++;
	}
	return (i - 1);
}

int	ft_putnbr_unsigned(unsigned int nb)
{
	int	i;

	i = 0;
	ft_putnbr_base(nb, "0123456789");
	if (nb == 0)
		i++;
	while (nb > 0)
	{
		nb /= 10;
		i++;
	}
	return (i - 1);
}
