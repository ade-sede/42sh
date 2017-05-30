/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 01:26:22 by ade-sede          #+#    #+#             */
/*   Updated: 2017/05/30 16:11:33 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H
# include <stdarg.h>
# include "libft.h"
# include <wchar.h>
# define H 6
# define HH 12
# define L 4
# define LL 8
# define J 1
# define Z 2
# define RED "\x1B[31m"
# define GRN "\x1B[32m"
# define YEL "\x1B[33m"
# define BLU "\x1B[34m"
# define MAG "\x1B[35m"
# define CYN "\x1B[36m"
# define WHT "\x1B[37m"
# define RESET "\x1B[0m"
# define OCT 1
# define HEX 1001
# define INT 1002
# define STR 1003
# define CHAR 1004

typedef	struct	s_opt
{
	int			exc;
	int			dot_flag;
	int			conv_index;
	int			sharp_flag;
	int			plus_flag;
	int			minus_flag;
	int			space_flag;
	char		printf_pad_char;
	int			field_len;
	int			prec;
	int			len_mod;
	char		*conv_base;
	char		*opt_base;
	char		*flag_base;
	char		*digit_base;
	char		*len_mod_base;
	char		*place_holder;
	char		conv_flag;
	int			conv_ret;
}				t_opt;

void			last_join(char **buffer, char *format, int *ret);
void			ft_exception(t_opt **opt, char *str);
int				is_opt(char c);
int				is_len_mod(char c);
int				conv_type(t_opt **opt);
int				get_form_size(t_opt **opt, int neg);
void			add_form(char **str, t_opt **opt, int neg_sign);
void			add_prec(char **str, t_opt **opt);
void			add_flags(char **str, t_opt **opt);
char			*pad(int pad_size, char c);
void			create_field(char **str, t_opt **opt, int form_size);
int				start_conv(char **buffer, int *ret, const char *format,
		va_list ap);
void			early_join(char **buffer, char *little, int *ret);
void			fill_fcts(char *(**f)(t_opt**, va_list));
void			get_mode(t_opt **opt);
void			get_flags(t_opt **opt);
void			get_prec(t_opt **opt, va_list ap);
void			get_fields_info(t_opt **opt, va_list ap);
char			*ft_s(t_opt **opt, va_list ap);
char			*ft_upper_s(t_opt **opt, va_list ap);
char			*ft_u(t_opt **opt, va_list ap);
char			*ft_d(t_opt **opt, va_list ap);
char			*ft_c(t_opt **opt, va_list ap);
char			*ft_p(t_opt	**opt, va_list ap);
char			*ft_x(t_opt **opt, va_list ap);
char			*ft_upper_x(t_opt **opt, va_list ap);
char			*ft_o(t_opt **opt, va_list ap);
char			*ft_b(t_opt **opt, va_list ap);
int				ft_printf(const char *format, ...);
int				bufferise(char **buffer, const char *format, va_list ap);
char			*convert(const char *format, va_list ap, t_opt **opt, int *ret);
int				conv_is_valid(char c);
int				conv_size(const char *format);
t_opt			*get_opt(const char *format, va_list ap);
int				mode_is_valid(char c);
#endif
