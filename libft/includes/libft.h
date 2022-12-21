/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 12:56:56 by lorampon          #+#    #+#             */
/*   Updated: 2022/11/27 16:41:07 by lorampon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

long int	ft_atoi(const char *str);
void		ft_bzero(void *str, int n);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);
char		*ft_itoa(int n);
char		*ft_itob(int nbr);
int			ft_btoi(void *ptr);
void		*ft_memset(void *ptr, int value, size_t size);
int			ft_memcmp(const void *ptr1, const void *ptr2, size_t size);
void		*ft_memcpy(void	*dest, const void *src, size_t size);
void		*ft_memmove(void *dest, const void *src, size_t size);
void		*ft_memchr(const void *mem, int c, size_t size);
char		*ft_strchr(const char *str, int c);
char		*ft_strdup(const char *src);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strtrim(char const *s1, char const *set);
size_t		ft_strlcat(char *dest, const char *src, size_t size);
size_t		ft_strlcpy(char *dest, const char *src, size_t size);
size_t		ft_strlen(const char *str);
int			ft_strncmp(const char *s1, const char *s2, size_t length);
char		*ft_strnstr(const char *big, const char *little, size_t size);
char		*ft_strrchr(const char *str, int c);
void		ft_revstr(char *str);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char *));
char		*ft_substr(char const *s, unsigned int start, size_t len);
int			ft_tolower(int c);
int			ft_toupper(int c);
void		*ft_calloc(size_t count, size_t size);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int nb, int fd);
t_list		*ft_lstnew(void	*content);
void		ft_lstadd_front(t_list **lst, t_list *new);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
int			ft_putchar(char c);
int			ft_conversion(char specifier, va_list param);
int			ft_printf(const char *str, ...);
int			ft_putstr(char *str);
int			ft_pourcent(void);
void		ft_putnbr_base(unsigned long long nb, char *base);
int			ft_putnbr_hexa_low(unsigned int nb);
int			ft_putnbr_hexa_up(unsigned int nb);
int			ft_ptrhexa(void *ptr);
int			ft_putnbr(int nbr);
int			ft_putnbr_unsigned(unsigned int nb);
int			ft_strcmp(char *s1, char *s2);
char		*ft_strcpy(char *dest, char *src);
char		**ft_split(const char *str, char c);

#endif
