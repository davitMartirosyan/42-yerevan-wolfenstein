/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_algo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 10:27:49 by dmartiro          #+#    #+#             */
/*   Updated: 2023/04/24 20:23:33 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_game_tsc(int x, t_game *game)
{
	game->tsc.cameraX = 2 * x / (double) W - 1;
	game->tsc.rayDirX = game->player->dir.x + game->player->plane.x
		* game->tsc.cameraX;
	game->tsc.rayDirY = game->player->dir.y + game->player->plane.y
		* game->tsc.cameraX;
	game->tsc.mapX = (int)game->player->pos.x;
	game->tsc.mapY = (int)game->player->pos.y;
	game->tsc.sideDistX = 0;
	game->tsc.sideDistY = 0;
	game->tsc.deltaDistX = fabs(1 / game->tsc.rayDirX);
	game->tsc.deltaDistY = fabs(1 / game->tsc.rayDirY);
	game->tsc.perpWallDist = 0;
	game->tsc.stepX = 0;
	game->tsc.stepY = 0;
	game->tsc.hit = 0;
	game->tsc.side = 0;
	game->tsc.wall = 0;
}

void	check_rays(t_game *game)
{
	if (game->tsc.rayDirX < 0)
	{
		game->tsc.stepX = -1;
		game->tsc.sideDistX = (game->player->pos.x - game->tsc.mapX)
			* game->tsc.deltaDistX;
	}
	else
	{
		game->tsc.stepX = 1;
		game->tsc.sideDistX = (game->tsc.mapX + 1.0 - game->player->pos.x)
			* game->tsc.deltaDistX;
	}
	if (game->tsc.rayDirY < 0)
	{
		game->tsc.stepY = -1;
		game->tsc.sideDistY = (game->player->pos.y - game->tsc.mapY)
			* game->tsc.deltaDistY;
	}
	else
	{
		game->tsc.stepY = 1;
		game->tsc.sideDistY = (game->tsc.mapY + 1.0 - game->player->pos.y)
			* game->tsc.deltaDistY;
	}
}

void	dda_algorithm_loop(t_game *game)
{
	while (game->tsc.hit == 0)
	{
		if (game->tsc.sideDistX < game->tsc.sideDistY)
		{
			game->tsc.sideDistX += game->tsc.deltaDistX;
			game->tsc.mapX += game->tsc.stepX;
			game->tsc.side = 0;
		}
		else
		{
			game->tsc.sideDistY += game->tsc.deltaDistY;
			game->tsc.mapY += game->tsc.stepY;
			game->tsc.side = 1;
		}
		if (game->mmap && game->mmap[game->tsc.mapY][game->tsc.mapX] == 1)
			game->tsc.hit = 1;
	}		
}

void	start_end(int x, t_game *game)
{
	if (game->tsc.side == 0)
		game->tsc.perpWallDist = (game->tsc.mapX - game->player->pos.x
				+ (1 - game->tsc.stepX) / 2) / game->tsc.rayDirX;
	else
		game->tsc.perpWallDist = (game->tsc.mapY - game->player->pos.y
				+ (1 - game->tsc.stepY) / 2) / game->tsc.rayDirY;
	game->tsc.lineHeight = (int)(H / 2 / game->tsc.perpWallDist);
	game->tsc.drawStart = -game->tsc.lineHeight / 2 + H / 2;
	if (game->tsc.drawStart < 0)
		game->tsc.drawStart = 0;
	game->tsc.drawEnd = game->tsc.lineHeight / 2 + H / 2;
	if (game->tsc.drawEnd >= H)
		game->tsc.drawEnd = H - 1;
}
