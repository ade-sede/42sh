/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */ /*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 15:46:58 by ade-sede          #+#    #+#             */
/*   Updated: 2017/05/28 17:51:12 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <string.h>
# include "color.h"
# include "str.h"
# include "mem.h"
# include "alloc.h"
# include "list.h"
# include "array.h"
# define MALLOC_ERROR 666
# define TRUE 1
# define FALSE 0
# define EXIT_FAILURE 1
# define EXIT_SUCCESS 0
# define WHITESPACES " 	\n\t\v"
# define IS_WHITESPACE(c) (c == 32 || c == '\t' || c == '\n')
# define PRINTF_SIZEOF(type) printf("sizeof(" #type ") = %zd.\n", sizeof(type))
# define ft_ishex(x) ft_is_hex(x)

# ifndef T_ULONG
#  define T_ULONG
typedef unsigned long int t_ulong;
# endif

typedef struct		s_coordinates
{
	int		x;
	int		y;
}					t_coordinates;


typedef struct		s_btree
{
	struct s_btree	*left;
	struct s_btree	*right;
	struct s_btree	*parent;
	void			*data;
}					t_btree;

/*
** In file ft_abs.c
*/

intmax_t			ft_abs(intmax_t value);

/*
** In file ft_atoi.c
*/

int					ft_atoi(const char *str);
int					ft_atoi_safe(const char *str, int *result);
intmax_t			ft_atoi_base(char *str, int base);

/*
**	In file ft_is_1.c
*/

int					ft_isdigit(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_isalpha(int c);
int					ft_isalnum(int c);

/*
**	In file ft_is_2.c
*/

int					ft_is_hex(int c);
int					ft_is_upper(char c);
int					ft_is_lower(char c);
int					ft_is_space(char c);
int					ft_is_one_of(char c, const char *that);


/*
**	In file ft_is_3.c
*/

int					is_quote(int c);

/*
** 	In file toupper.c
*/

int					ft_toupper(int c);
char				*ft_upstr(char *s);

/*
**	In file tolower.c
*/


int					ft_tolower(int c);
char				*ft_lowstr(char *s);

/*
**	In file itoa.c
*/

char				*ft_itoa(int n);
char				*ft_itoa_base(intmax_t value, int base);
char				*ft_unsigned_itoa_base(uintmax_t value, int base);


/*
**	Fatal.c
*/

void				fatal(const char *error_str);
#endif

