/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <maissa-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 14:46:22 by nbelouni          #+#    #+#             */
/*   Updated: 2017/03/20 16:55:37 by maissa-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>

# include "error.h"
# include "color.h"
# include "option.h"

# define BUFF_SIZE 2048

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
size_t				ft_strlen(const char *s);
void				ft_putstr(const char *s);
char				*ft_strdup(const char *s1);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, unsigned int n);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2, unsigned int n);
unsigned int		ft_strlcat(char *dst, const char *src, unsigned int n);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *s1, const char *s2);
char				*ft_strnstr(const char *s1, const char *s2, unsigned int n);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, unsigned int n);
int					ft_atoi(const char *str);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void(*f)(char *));
void				ft_striteri(char *s, void(*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, int c);
char				*ft_itoa(int n);
void				ft_putchar(char c);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
int					ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void				ft_lstpush(t_list **begin, void const *s, size_t s_size);
int					get_next_line(int const fd, char **line);

int					ft_print_error(char *cmd, char *err, int ret);
int					ft_is_valid_dir(const char *pathname);
int					ft_get_index_of(char *str, char c);
char				*ft_strcut(char *str, char c);
int					ft_strisdigit(char *str);
char				*ft_epurstr(char *str);
char				*ft_tabconcat(char **tab);
void				ft_puttab(char **tab);
size_t				ft_tablen(char **tab);
void				ft_multi_free(char *s1, char *s2, char *s3, char *s4);
char				*ft_multi_concat(char *s1, char *s2, char *s3, char *s4);
char				*ft_multi_join(char *s1, char *s2, char *s3, char *s4);
char				*ft_free_and_dup(char *dst, char *src);
char				*ft_strlchr(char *str, char c);
char				*ft_free_and_join(char *str1, char *str2);
void				ft_tabdel(char **tab);
void				ft_tabdel_and_init(char ***tab);
char				*ft_strreplace(char *o, const char *s, const char *r);
int					ft_intlen(int n);
void				ft_putnchar(char c, int n);

#endif
