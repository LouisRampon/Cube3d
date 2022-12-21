/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jereverd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 12:29:39 by jereverd          #+#    #+#             */
/*   Updated: 2021/12/13 12:29:43 by jereverd         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include "../libft/includes/libft.h"

# define BUFFER_SIZE 1

char	*get_next_line(int fd);
char	*ft_strjoinl_gnl(char *s1, char *s2, size_t i, size_t j);
int		check_buffer(char *line);


#endif
