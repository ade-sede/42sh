/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_struct.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 14:05:46 by ade-sede          #+#    #+#             */
/*   Updated: 2017/09/18 14:06:00 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOB_STRUCT_H
# define GLOB_STRUCT_H

typedef	struct	s_matches
{
	t_list	*list;
	char	*to_match;
	char	*regex;
	char	*dir;
}				t_matches;

#endif
