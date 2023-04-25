/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 03:19:25 by dmartiro          #+#    #+#             */
/*   Updated: 2023/04/24 19:57:27 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_player(t_game *game, int pos_dir, int x, int y);
static int	x_val(t_game *game, int x, int y, int *shooter);

int	player(t_game *game)
{
	int	shooter;
	int	y;
	int	x;

	y = 0;
	shooter = 0;
	while (y < game->map_h)
	{
		x = 0;
		if (!x_val(game, x, y, &shooter))
			return (0);
		y++;
	}
	if (shooter != 1)
		return (0);
	return (1);
}

static int	x_val(t_game *game, int x, int y, int *shooter)
{
	while (x < game->map_w)
	{
		if (game->mmap[y][x] == 30 || game->mmap[y][x] == 35
			|| game->mmap[y][x] == 39 || game->mmap[y][x] == 21)
		{
			if (!checkall(game->mmap, y, x, game->map_h - 1))
				return (0);
			set_player(game, game->mmap[y][x], x, y);
			*shooter += 1;
		}
		x++;
	}
	return (1);
}

static void	set_player(t_game *game, int pos_dir, int x, int y)
{
	game->player->pos.x = x + 0.5;
	game->player->pos.y = y + 0.5;
	game->mmap[y][x] = 0;
	if (pos_dir == 30)
		game->player->angle = 90;
	else if (pos_dir == 35)
		game->player->angle = 270;
	else if (pos_dir == 39)
		game->player->angle = 180;
	else if (pos_dir == 21)
		game->player->angle = 0;
	else
		game->player->angle = -1;
	game->player->cdir = degree_to_radian(
			replace_angle_360(game->player->angle));
	game->player->dir.x = cos(degree_to_radian(game->player->angle));
	game->player->dir.y = -1 * sin(degree_to_radian(game->player->angle));
	game->player->plane.x = -0.66 * game->player->dir.y;
	game->player->plane.y = 0.66 * game->player->dir.x;
}
