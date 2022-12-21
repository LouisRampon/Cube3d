/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 18:26:33 by lorampon          #+#    #+#             */
/*   Updated: 2022/05/03 13:15:43 by lorampon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (0);
}

int	ft_putstr(char *str)
{
	int	i;

	i = 0;
	if (!str)
	{
		ft_putstr("(null)");
		return (5);
	}
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i - 1);
}

int	ft_pourcent(void)
{
	write(1, "%", 1);
	return (0);
}

void	ft_putnbr_base(unsigned long long int nb, char *base)
{
	unsigned long long int	len;

	len = ft_strlen(base);
	if (nb >= len)
	{
		ft_putnbr_base(nb / len, base);
		ft_putnbr_base(nb % len, base);
	}
	else
		ft_putchar(base[nb]);
}
