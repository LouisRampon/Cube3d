/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 12:01:13 by lorampon          #+#    #+#             */
/*   Updated: 2022/06/03 15:51:59 by lorampon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*dest;

	i = 0;
	if (!s || !f)
		return (0);
	dest = malloc(ft_strlen(s) + 1);
	if (!dest)
		return (0);
	while (s[i])
	{
		dest[i] = (f)(i, s[i]);
		if (!dest[i])
			return (0);
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
