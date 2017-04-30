/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 14:38:25 by ade-sede          #+#    #+#             */
/*   Updated: 2017/04/21 14:39:00 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	main(int ac, char *av[], char **env)
{
	extern char **environ;

	int	i = 0;

	environ[44] = "test";
	if (environ[i] == NULL){
		printf("This is a noope\n");
	}
	while (environ[i])
	{
		printf("%s\n", environ[i]);
		i++;
	}
	return (0);
}
