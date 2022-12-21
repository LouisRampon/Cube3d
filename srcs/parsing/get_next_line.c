/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jereverd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 12:29:34 by jereverd          #+#    #+#             */
/*   Updated: 2021/12/13 12:29:35 by jereverd         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"

char	*ft_strjoin_gnl(char *s1, char *s2, size_t i, size_t j)
{
	char		*str;
	size_t		len_s1;
	size_t		len_s2;

	if (s1 == NULL && !s2)
		return (NULL);
	len_s1 = ft_strlen((char *)s1);
	len_s2 = ft_strlen((char *)s2);
	str = malloc((len_s1 + len_s2 + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	while (++i < len_s1)
		str[i] = s1[i];
	while ((s2[j] != '\n') && (j < len_s2))
		str[i++] = s2[j++];
	if (s2 && s2[j] == '\n')
		str[i++] = s2[j];
	str[i] = '\0';
	free(s1);
	return (str);
}

static char	*ft_save_rest(char *buffer)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (buffer[i] != '\n')
		i++;
	i += 1;
	while (buffer[i])
	{
		buffer[j] = buffer[i];
		i++;
		j++;
	}
	buffer[j] = '\0';
	return (buffer);
}

int	security_ret(int ret, char *line)
{
	if (ret == -1)
	{
		free(line);
		return (-1);
	}
	return (0);
}

static int	security_line(char *line)
{
	if (line == NULL || line[0] == 0)
	{
		free(line);
		return (-1);
	}
	return (1);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	buffer[BUFFER_SIZE + 1] = {0};
	int			read_ret;

	line = NULL;
	read_ret = 1;
	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE < 1)
		return (NULL);
	while (read_ret > 0)
	{
		line = ft_strjoin_gnl(line, buffer, -1, 0);
		if (check_buffer(buffer) == 1)
		{
			ft_save_rest(buffer);
			return (line);
		}
		read_ret = read(fd, buffer, BUFFER_SIZE);
		if (security_ret(read_ret, line) == -1)
			return (NULL);
		buffer[read_ret] = '\0';
	}
	if (security_line(line) == -1)
		return (NULL);
	return (line);
}
