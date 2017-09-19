/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 14:05:50 by ade-sede          #+#    #+#             */
/*   Updated: 2017/09/18 14:06:31 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_H
# define ARRAY_H
# include <string.h>

size_t		ft_arraylen(const char **str);
/*
** In file arraydup.c
*/

char		**ft_arraydup(const char **original);

void		ft_arraydel(char ***tab);
const char	**ft_arraychr(const char **array, const char *str);
size_t		ft_arraymax_f(char **str, size_t (*f)(char *));
#endif
