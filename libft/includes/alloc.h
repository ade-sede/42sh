/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 19:37:48 by ade-sede          #+#    #+#             */
/*   Updated: 2017/05/24 20:01:20 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALLOC_H
# define ALLOC_H
# include <stdlib.h>

/*
**	In file palloc.c
*/

void	*palloc(size_t size);

/*
**	In file ft_memalloc.c
*/

void	*ft_memalloc(size_t size);

/*
**	In file ft_calloc.c
*/

void	*ft_calloc(size_t count, size_t size);

#endif
