/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_to_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jereverd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 19:16:38 by jereverd          #+#    #+#             */
/*   Updated: 2022/12/19 19:16:40 by jereverd         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	*ft_copy_data(t_lst *cursor, int width)
{
	char	*str;
	int		i;

	str = ft_calloc(width + 1, sizeof (char));
	if (!str)
		ft_error_exit("Malloc failure\n");
	i = 0;
	while (cursor->line[i] && cursor->line[i] != '\n')
	{
		str[i] = cursor->line[i];
		i++;
	}
	while (i < width)
	{
		str[i] = space;
		i++;
	}
	return (str);
}

char	**ft_list_to_tab(t_lst *lst, int width, int height)
{
	int		i;
	char	**tab;
	t_lst	*cursor;

	cursor = lst;
	tab = ft_calloc(height + 1, sizeof(void *));
	if (!tab)
		ft_error_exit("Malloc failure\n");
	i = 0;
	while (cursor && tab)
	{
		tab[i] = ft_copy_data(cursor, width);
		i++;
		cursor = cursor->next;
	}
	return (tab);
}
