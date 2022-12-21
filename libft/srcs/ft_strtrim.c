/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 13:23:47 by lorampon          #+#    #+#             */
/*   Updated: 2022/05/03 13:16:37 by lorampon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*output;
	int		i;
	int		length;
	int		start;

	if (!s1 || !set)
		return (0);
	if (set[0] == 0)
		return (ft_strdup(s1));
	length = ft_strlen(s1);
	i = length;
	while (--i >= 0 && ft_strchr(set, s1[i]))
		length--;
	i = -1;
	while (length > 0 && s1[++i] && ft_strchr(set, s1[i]))
		length--;
	start = i;
	output = ft_calloc(length + 1, sizeof (char));
	if (!output)
		return (0);
	i = -1;
	while (++i < length)
		output[i] = s1[i + start];
	return (output);
}
