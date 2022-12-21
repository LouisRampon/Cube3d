/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 17:36:21 by lorampon          #+#    #+#             */
/*   Updated: 2022/12/02 17:10:51 by lorampon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t length)
{
	size_t	i;
	int		a;

	i = 0;
	while (i < length && (s1[i] || s2[i]))
	{
		if (s1[i] < s2[i] || s1[i] > s2[i])
		{
			a = (unsigned char)s1[i] - (unsigned char)s2[i];
			return (a);
		}
		i++;
	}
	return (0);
}
