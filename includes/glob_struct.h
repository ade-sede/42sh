/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_struct.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 22:42:10 by vcombey           #+#    #+#             */
/*   Updated: 2017/10/11 22:42:13 by vcombey          ###   ########.fr       */
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
