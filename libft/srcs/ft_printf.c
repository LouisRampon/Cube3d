/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 16:28:39 by lorampon          #+#    #+#             */
/*   Updated: 2022/06/03 15:52:27 by lorampon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_conversion(char specifier, va_list param)
{
	int	size;

	size = 0;
	if (specifier == 'c')
		size = ft_putchar((int)va_arg(param, int));
	else if (specifier == 's')
		size = ft_putstr((char *)va_arg(param, char *));
	else if (specifier == 'p')
		size = ft_ptrhexa((void *)va_arg(param, void *));
	else if (specifier == 'i' || specifier == 'd')
		size = ft_putnbr((int)va_arg(param, int));
	else if (specifier == 'u')
		size = ft_putnbr_unsigned((unsigned int)va_arg(param, unsigned int));
	else if (specifier == 'x')
		size = ft_putnbr_hexa_low((unsigned int)va_arg(param, unsigned int));
	else if (specifier == 'X')
		size = ft_putnbr_hexa_up((unsigned int)va_arg(param, unsigned int));
	else if (specifier == '%')
		size = ft_pourcent();
	return (size);
	va_end(param);
}

int	ft_printf(const char *str, ...)
{
	size_t	i;
	int		size;
	va_list	param;

	i = 0;
	size = 0;
	va_start(param, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			size += ft_conversion(str[i], param);
		}
		else
			ft_putchar(str[i]);
		i++;
		size++;
	}
	va_end(param);
	return (size);
}
