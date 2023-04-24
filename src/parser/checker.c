/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 19:00:40 by tumolabs          #+#    #+#             */
/*   Updated: 2023/04/24 19:30:56 by dmartiro         ###   ########.fr       */
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
				if (!checkall(game->mmap, y, x, game->map_h - 1))
					return (0);
			x++;
		}
		y++;
	}
	return (1);
}

int	checkall(int **mmap, int y, int x, int h)
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

void	check_dependancies(t_game *game)
{
	t_texture	*t;
	int			i;

	t = game->texture;
	t[0].file = mlx_xpm_file_to_image(game->screen->mlx,
			path(game->north), &t[0].w, &t[0].h);
	t[1].file = mlx_xpm_file_to_image(game->screen->mlx,
			path(game->south), &t[1].w, &t[1].h);
	t[2].file = mlx_xpm_file_to_image(game->screen->mlx,
			path(game->west), &t[2].w, &t[2].h);
	t[3].file = mlx_xpm_file_to_image(game->screen->mlx,
			path(game->east), &t[3].w, &t[3].h);
	i = -1;
	while (++i < 4)
		if (!t[i].file)
			failure();
	i = -1;
	while (++i < 4)
		t[i].img = (char *)mlx_get_data_addr(t[i].file, &t[i].bpp,
				&t[i].size, &t[i].endian);
}
