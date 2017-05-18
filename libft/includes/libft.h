/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 15:46:58 by ade-sede          #+#    #+#             */
/*   Updated: 2017/05/18 17:42:34 by ade-sede         ###   ########.fr       */
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
# include <fcntl.h>
# include <sys/types.h>
# define MALLOC_ERROR 666
# define true 1
# define false 0
# define TRUE 1
# define FALSE 0
# define EXIT_FAILURE 1
# define EXIT_SUCCESS 0

typedef unsigned long int t_ulong;

typedef struct		s_coordinates
{
	int		x;
	int		y;
}					t_coordinates;

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
	int				node_count;
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
char				*ft_itoa(int n);
char				**ft_strsplit(const char *str, const char *split_base);
int					ft_putchar(int c);
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
void				ft_sort_int_tab(int *tabb, size_t n);
int					ft_sqrt(int nb);
int					ft_power(int nb, int power);
char				*ft_itoa_base(intmax_t value, int base);
ssize_t				ft_strichr(const char *s, char c);
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
void				*ft_str_realloc(size_t ptr_data_size, void *ptr, size_t size);
void				**ft_addcpy(void **dst, const void **src, size_t n);
void				**ft_array_realloc(size_t ptr_data_size, void **ptr, size_t size);
size_t				ft_arraylen(const char **s);
void				**ft_array_remove(int index, size_t ptr_data_size, void **ptr);
void				ft_lst_replace_middle(t_lst_head **head);
void				fatal(const char *error_str);
void				ft_double_lst_foreach(t_list_d *start, t_list_d *end, void (*f)(t_list_d*), int order);
void				ft_simple_lst_foreach(t_list *start, t_list *end, void (*f)(t_list*));
void				ft_simple_lst_for_n(t_list *start, int count, void (*f)(t_list*));
void				ft_double_lst_for_n(t_list_d *start, int count, void (*f)(t_list_d*), int order);
void				ft_double_lst_del_one(t_lst_head **head, t_list_d *node, void (*f)(void*));
void				ft_double_lst_remove(t_lst_head **head, void (*f)(void*));
void				ft_remove_head(t_lst_head **head, void (*f)(void*));
t_list_d			*ft_double_lst_get_n(t_list_d *first, int n);
t_list				*ft_simple_lst_get_n(t_list	*first, size_t n);
void				ft_simple_lst_del_one(t_list **first, t_list *node, void(*f)(void*));
void				ft_simple_lst_remove(t_list	**first, void (*f)(void*));
t_list				*ft_simple_lst_return_if(t_list *node, int (*f)(void*));
t_list_d			*ft_double_lst_return_if(t_list_d *node, int (*f)(void*));
void				ft_free(void *p);
char				**ft_arraydup(const char **original);
unsigned long int		ft_freeswap(unsigned long int old, unsigned long int new);
int				charcmp(const char *str, int index, char *char_base);
char				*ft_strsurround(const char *s1, const char *s2, const char *s3);
short int			bs_str(const char *str, int i, char c);
void				ft_simple_lst_dup(t_list **new_list_first, t_list *original);
void				ft_arraydel(char ***tab);
#endif
