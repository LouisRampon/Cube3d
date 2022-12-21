/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jereverd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 19:16:27 by jereverd          #+#    #+#             */
/*   Updated: 2022/12/19 19:16:30 by jereverd         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_lst	*ft_new_node(char *str)
{
	t_lst	*node;

	node = malloc(sizeof(t_lst));
	if (node == NULL)
		return (NULL);
	node->line = str;
	node->next = NULL;
	return (node);
}

void	ft_push_back_lst_elem(t_lst **lst, t_lst *node)
{
	t_lst	*cursor;

	cursor = *lst;
	if (!*lst)
		*lst = node;
	else
	{
		while (cursor->next)
			cursor = cursor->next;
		cursor->next = node;
	}
}

void	ft_add_node_to_lst(t_lst **lst, char *str)
{
	t_lst	*new;

	new = ft_new_node(str);
	if (!new)
	{
		ft_free_lst(*lst);
		ft_error_exit("Failed to add a node to lst\n");
	}
	ft_push_back_lst_elem(lst, new);
}

void	ft_free_lst(t_lst *lst)
{
	t_lst	*ptr;

	ptr = lst;
	while (ptr)
	{
		ptr = lst->next;
		free(lst->line);
		free(lst);
		lst = NULL;
		lst = ptr;
	}
}
