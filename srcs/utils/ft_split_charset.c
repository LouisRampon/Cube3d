/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_charset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jereverd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 19:17:20 by jereverd          #+#    #+#             */
/*   Updated: 2022/12/19 19:17:22 by jereverd         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

typedef struct s_var
{
	int	i;
	int	j;
	int	len;
}t_var;

int	is_charset(char *str, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (*str == charset[i])
			return (1);
		i++;
	}
	return (0);
}

int	count_word(char *str, char *charset)
{
	int	count;

	count = 0;
	while (is_charset(str, charset) == 1)
		str++;
	while (*str)
	{
		if (is_charset(str, charset) == 1)
		{
			while (is_charset(str, charset) == 1)
				str++;
			if (*str != '\0')
				count++;
		}
		else
			str++;
	}
	return (count + 1);
}

int	wordlen(char *str, char *charset)
{
	int	i;

	i = 0;
	while (is_charset(str, charset) == 1)
		str++;
	while (str[i] && is_charset(str + i, charset) == 0)
		i++;
	return (i);
}

char	*skip_charsets(char *str, char *charset)
{
	while (is_charset(str, charset) > 0)
		str++;
	return (str);
}

char	**ft_split_charset(char *str, char *charset)
{
	char	**tab;
	t_var	var;

	if (!str || !charset)
		return (NULL);
	var.i = 0;
	tab = malloc(sizeof(*tab) * (count_word(str, charset) + 1));
	if (!tab)
		return (NULL);
	str = skip_charsets(str, charset);
	while (*str)
	{
		tab[var.i] = malloc(sizeof(char) * (wordlen(str, charset) + 1));
		if (!(tab[var.i]))
			return (NULL);
		var.len = wordlen(str, charset);
		var.j = 0;
		while (var.j < var.len)
			tab[var.i][var.j++] = *(str++);
		tab[var.i][var.j] = '\0';
		var.i++;
		str = skip_charsets(str, charset);
	}
	tab[var.i] = 0;
	return (tab);
}
