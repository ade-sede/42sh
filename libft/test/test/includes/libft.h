/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 15:46:58 by ade-sede          #+#    #+#             */
/*   Updated: 2017/04/28 17:23:35 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <wchar.h>
# include <limits.h>
# include <stdint.h>
# define MALLOC_ERROR 666



typedef struct		s_list
{
	struct s_list	*next;
	void			*data;
}					t_list;

typedef struct		s_list_d
{
	struct s_list_d	*next;
	struct s_list_d	*prev;
	void			*data;
}					t_list_d;

typedef struct		s_btree
{
	struct s_btree	*left;
	struct s_btree	*right;
	struct s_btree	*parent;
	void			*data;
}					t_btree;

typedef struct		s_lst_head
{
	struct s_list_d	*first;
	struct s_list_d	*middle;
	struct s_list_d	*last;
	int				shift_middle;
}					t_lst_head;

t_list				*ft_simple_lst_create(void *data);
t_list_d			*ft_double_lst_create(void *data);
t_lst_head			*ft_create_head(t_list_d *first);
void				ft_lst_insert_before_middle(t_lst_head **head, t_list_d *new_node, int(*f)(t_list_d*, t_list_d*));
void				ft_lst_insert_after_middle(t_lst_head **head, t_list_d *new_node, int(*f)(t_list_d*, t_list_d*));
void				ft_simple_lst_sort_insert(t_list **first, t_list *new_node, int (*f)(t_list*, t_list*));
void				ft_double_lst_sort_insert(t_lst_head **head, t_list_d *new_node, int (*f)(t_list_d*, t_list_d*));
void				ft_double_lst_pushback(t_lst_head **head, t_list_d *new_node);
void				ft_double_lst_add(t_lst_head **head, t_list_d *new_node);
void				ft_simple_lst_pushback(t_list **first, t_list *new_node);
void				ft_simple_lst_add(t_list **first, t_list *new_node);
void				libft_error(int error_code, const char *function_name);
void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
size_t				ft_strlen(const char *s);
char				*ft_strdup(const char *s1);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *big, const char *little);
char				*ft_strnstr(const char *s1, const char *s2, size_t n);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_atoi(const char *str);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
char				*ft_upstr(char *s);
char				*ft_lowstr(char *s);
int					ft_tolower(int c);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char*));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
char				*ft_itoa(int n);
void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
int					ft_digit_count(int nb);
char				*ft_strrev(char *str);
int					ft_is_upper(char c);
int					ft_is_lower(char c);
int					ft_is_space(char c);
char				*ft_strndup(char *str, size_t n);
void				ft_sort_int_tab(int *tab, size_t n);
int					ft_sqrt(int nb);
int					ft_power(int nb, int power);
char				*ft_itoa_base(intmax_t value, int base);
ssize_t				ft_strichr(char *s, char c);
int					divide(int a, int b);
int					mod(int a, int b);
int					mult(int a, int b);
int					plus(int a, int b);
int					min(int a, int b);
char				*ft_buff_wchar(wchar_t c);
int					ft_strmatch(char *s1, char *s2);
intmax_t			ft_abs(intmax_t value);
char				*ft_buff_wstring(wchar_t *str);
int					ft_ishex(int c);
void				ft_strtrunc(char **str, int size_left);
void				ft_strnreplace(char *str, char target, char replace, int size);
intmax_t			ft_atoi_base(char *str, int base);
char				*ft_chartostr(char c);
char				*ft_unsigned_itoa_base(uintmax_t, int);
void				*palloc(size_t size, const char *func_name);
void				*ft_strchange(void *old, void *new);
char				*ft_strsurround(char *s1, char *s2, char *s3);
void				*ft_str_realloc(size_t ptr_data_size, void *ptr, size_t size);
void				**ft_addcpy(void **dst, const void **src, size_t n);
void				**ft_array_realloc(size_t ptr_data_size, void **ptr, size_t size);
size_t				ft_arraylen(const char **s);
#endif
