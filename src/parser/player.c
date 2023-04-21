/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 03:19:25 by dmartiro          #+#    #+#             */
/*   Updated: 2023/04/21 13:44:04 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void     set_player(t_game *game, int pos_dir);

int player(t_game *game)
{
    int shooter;
    int y;
    int x;
    
    y = 0;
    shooter = 0;
    while (y < game->map_h)
    {
        x = 0;
        while (x < game->map_w)
        {
            if (game->mmap[y][x] == 30 || game->mmap[y][x] == 35
                || game->mmap[y][x] == 39 || game->mmap[y][x] == 21)
            {
				if (!checkall(game->mmap, y, x, game->map_w - 1, game->map_h - 1))
					return (0);
                game->player->pos.x = x + 0.5;
                game->player->pos.y = y + 0.5;
                set_player(game, game->mmap[y][x]);
                game->mmap[y][x] = 0;
                shooter++;
            }
            x++;
        }
        y++;
    }
    if (shooter != 1)
        return (0);
	return (1);
}

static void    set_player(t_game *game, int pos_dir)
{
	if (pos_dir == 30)
		game->player->angle = 90;
	else if (pos_dir == 35)
		game->player->angle = 270;
	else if (pos_dir == 39)
		game->player->angle = 0;
	else if (pos_dir == 21)
		game->player->angle = 180;
	else
		game->player->angle = -1;
	game->player->cdir = degree_to_radian(replace_angle_360(game->player->angle)); // 90 astichan depi verev
	game->player->dir.x = cos(degree_to_radian(game->player->angle));
	game->player->dir.y = -1 * sin(degree_to_radian(game->player->angle));
	game->player->plane.x = -0.66 * game->player->dir.y;
	game->player->plane.y = 0.66 * game->player->dir.x;
}