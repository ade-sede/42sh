/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 22:42:10 by vcombey           #+#    #+#             */
/*   Updated: 2017/10/11 22:42:13 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCAL_H
# define LOCAL_H

# include "libft.h"

char	*key_of_local(char *data, int c);
char	*value_of_local(char *data, int c);

char	*local_get_var(t_list *local, char *key_want);
int		add_to_local(t_list **local, char *data);
int		remove_var_from_local(t_list **local, char *key);

#endif
