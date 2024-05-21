/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 16:05:47 by a0ec6397          #+#    #+#             */
/*   Updated: 2024/05/21 15:03:19 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <fcntl.h>
# include <limits.h>
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int					ft_atoi(const char *str);
void				ft_bzero(void *str, size_t len);
void				*ft_calloc(size_t count, size_t size);
int					ft_isalnum(int x);
int					ft_isalpha(int x);
int					ft_isascii(int x);
int					ft_isdigit(int x);
int					ft_isprint(int x);
void				*ft_memchr(const void *str, int c, size_t n);
int					ft_memcmp(const void *str1, const void *str2, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t numBytes);
void				*ft_memmove(void *dest, const void *src, size_t numBytes);
void				*ft_memset(void *str, int value, size_t len);
char				*ft_strchr(const char *str, int c);
char				*ft_strdup(const char *str);
size_t				ft_strlcat(char *dest, const char *src, size_t size);
size_t				ft_strlcpy(char *dest, const char *src, size_t size);
size_t				ft_strlen(const char *str);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strnstr(const char *str, const char *to_find,
						size_t len);
char				*ft_strrchr(const char *s, int c);
int					ft_tolower(int i);
int					ft_toupper(int i);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *str, char c);
char				*ft_itoa(int n);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new_node);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new_node);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
unsigned int		ft_putnbr(int n);
int					ft_strcmp(const char *s1, const char *s2);
void				ft_strcpy(char *dest, const char *src);
int					ft_printf(const char *str, ...);
unsigned int		ft_put_char(int c);
unsigned int		ft_put_string(char *str);
unsigned int		ft_put_hex_pointer(size_t ptr);
unsigned int		ft_putnbr_unsigned(unsigned int n);
unsigned int		ft_put_hex_uint_lower(unsigned int i);
unsigned int		ft_put_hex_uint_upper(unsigned int i);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*get_next_line(int fd);
size_t				get_int_len(int n);

#endif