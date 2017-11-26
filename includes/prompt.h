/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:38 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:45 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H
# ifndef RED
#  define RED "\x1B[1;31m"
# endif
# ifndef GRN
#  define GRN "\x1B[1;32m"
# endif
# ifndef YEL
#  define YEL "\x1B[1;33m"
# endif
# ifndef BLU
#  define BLU "\x1B[1;34m"
# endif
# ifndef MAG
#  define MAG "\x1B[35m"
# endif
# ifndef CYN
#  define CYN "\x1B[36m"
# endif
# ifndef WHT
#  define WHT "\x1B[37m"
# endif
# ifndef RESET
#  define RESET "\x1B[0m"
# endif

char						*get_git_status(size_t *len);
char						*get_current_directory(void);
char						*get_ps1(t_env *env, size_t *len);
#endif
