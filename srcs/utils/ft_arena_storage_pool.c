/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_storage_pool.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:19:44 by jereverd          #+#    #+#             */
/*   Updated: 2022/12/05 17:21:37 by lorampon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_init_arena(t_data *d, size_t size)
{
	d->arena = malloc(sizeof(t_arena));
	if (d->arena)
	{
		d->arena->cursor = 0;
		d->arena->size = size;
		d->arena->data = malloc(d->arena->size);
		d->arena->next = 0;
	}
	if (!d->arena || !d->arena->data)
	{
		perror("minishell");
		exit(EXIT_FAILURE);
	}
}

void	ft_free_arena(t_arena *arena)
{
	t_arena	*current;
	t_arena	*next;

	current = arena;
	while (current)
	{
		next = current->next;
		free(current->data);
		free(current);
		current = next;
	}
}

static int	ft_arena_realloc(t_arena *arena, size_t size)
{
	size_t	new_size;
	t_arena	*new_node;

	if (size + arena->size > arena->size * 2)
		new_size = size + arena->size * 2;
	else
		new_size = arena->size * 2;
	new_node = malloc(sizeof(t_arena));
	if (new_node)
		new_node->data = malloc(new_size);
	if (new_node && new_node->data)
	{
		arena->next = new_node;
		new_node->size = new_size;
		new_node->cursor = 0;
		new_node->next = NULL;
		return (1);
	}
	else
	{
		perror("minishell: malloc");
		exit (EXIT_FAILURE);
	}
}

void	*ft_arena_alloc(t_arena *arena, size_t size)
{
	size_t	temp;

	while (arena->next && arena->cursor + size > arena->size)
		arena = arena->next;
	if (arena->cursor + size > arena->size)
		if (ft_arena_realloc(arena, size))
			arena = arena->next;
	temp = arena->cursor;
	arena->cursor += size;
	return (arena->data + temp);
}
