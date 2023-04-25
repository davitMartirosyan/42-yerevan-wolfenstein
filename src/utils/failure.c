/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   failure.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tumolabs <tumolabs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 00:08:18 by tumolabs          #+#    #+#             */
/*   Updated: 2023/04/24 20:04:51 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	failure(void)
{
	write(1, "Error!\n", 7);
	exit(1);
}

void	free_char_pp(char ***pp)
{
	int	i;

	i = -1;
	if (!(*pp) && !*(*pp))
		return ;
	while ((*pp)[++i])
		free((*pp)[i]);
	free((*pp));
	(*pp) = NULL;
}
