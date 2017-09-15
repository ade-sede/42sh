/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_struct.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 01:41:53 by vcombey           #+#    #+#             */
/*   Updated: 2017/09/16 01:42:55 by vcombey          ###   ########.fr       */
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
