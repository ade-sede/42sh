/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 18:38:11 by ade-sede          #+#    #+#             */
/*   Updated: 2017/05/29 16:54:28 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef ARRAY_H 
# define ARRAY_H
# include <string.h>

size_t	ft_arraylen(const char **str);
/*
** In file arraydup.c
*/

char	**ft_arraydup(const char **original);

/*
**	In file arraydel.c
*/


void	ft_arraydel(char ***tab);


/*
**	In file arraychr.c
*/

const char	**ft_arraychr(const char **array, const char *str);

/*
**	In file arraymax.c
*/

size_t		ft_arraymax_f(const char **str, size_t (*f)(const char *));
#endif