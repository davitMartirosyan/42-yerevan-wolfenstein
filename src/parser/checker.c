/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 19:00:40 by tumolabs          #+#    #+#             */
/*   Updated: 2023/04/18 05:35:53 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_board(t_game *game)
{
	int	x;
	int	y;
	
	y = 0;
	while (y < game->map_h)
	{
		x = 0;
		while (x < game->map_w)
		{
			if (game->mmap[y][x] == 0)
				if (!checkall(game->mmap, y, x, game->map_w - 1, game->map_h - 1))
					return (0);
			x++;
		}
		y++;
	}
	return (1);
}

int	checkall(int **mmap, int y, int x, int w, int h)
{
	if (y == 0 || y == h)
		return (0);
	else if (x == 0)
		return (0);
	else if (mmap[y - 1][x] == -1
		|| mmap[y + 1][x] == -1
		|| mmap[y][x - 1] == -1
		|| mmap[y][x + 1] == -1)
		return (0);
	return (1);
}