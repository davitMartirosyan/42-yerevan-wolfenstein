/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_algo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 10:27:49 by dmartiro          #+#    #+#             */
/*   Updated: 2023/04/25 19:05:39 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_game_tsc(int x, t_game *game)
{
	game->tsc.camera_x = 2 * x / (double) W - 1;
	game->tsc.ray_dir_x = game->player->dir.x + game->player->plane.x
		* game->tsc.camera_x;
	game->tsc.ray_dir_y = game->player->dir.y + game->player->plane.y
		* game->tsc.camera_x;
	game->tsc.mapx = (int)game->player->pos.x;
	game->tsc.mapy = (int)game->player->pos.y;
	game->tsc.side_dist_x = 0;
	game->tsc.side_dist_y = 0;
	game->tsc.delta_dist_x = fabs(1 / game->tsc.ray_dir_x);
	game->tsc.delta_dist_y = fabs(1 / game->tsc.ray_dir_y);
	game->tsc.perp_wall_dist = 0;
	game->tsc.stepx = 0;
	game->tsc.stepy = 0;
	game->tsc.hit = 0;
	game->tsc.side = 0;
	game->tsc.wall = 0;
}

void	check_rays(t_game *game)
{
	if (game->tsc.ray_dir_x < 0)
	{
		game->tsc.stepx = -1;
		game->tsc.side_dist_x = (game->player->pos.x - game->tsc.mapx)
			* game->tsc.delta_dist_x;
	}
	else
	{
		game->tsc.stepx = 1;
		game->tsc.side_dist_x = (game->tsc.mapx + 1.0 - game->player->pos.x)
			* game->tsc.delta_dist_x;
	}
	if (game->tsc.ray_dir_y < 0)
	{
		game->tsc.stepy = -1;
		game->tsc.side_dist_y = (game->player->pos.y - game->tsc.mapy)
			* game->tsc.delta_dist_y;
	}
	else
	{
		game->tsc.stepy = 1;
		game->tsc.side_dist_y = (game->tsc.mapy + 1.0 - game->player->pos.y)
			* game->tsc.delta_dist_y;
	}
}

void	dda_algorithm_loop(t_game *game)
{
	while (game->tsc.hit == 0)
	{
		if (game->tsc.side_dist_x < game->tsc.side_dist_y)
		{
			game->tsc.side_dist_x += game->tsc.delta_dist_x;
			game->tsc.mapx += game->tsc.stepx;
			game->tsc.side = 0;
		}
		else
		{
			game->tsc.side_dist_y += game->tsc.delta_dist_y;
			game->tsc.mapy += game->tsc.stepy;
			game->tsc.side = 1;
		}
		if (game->mmap && game->mmap[game->tsc.mapy][game->tsc.mapx] == 1)
			game->tsc.hit = 1;
	}		
}

void	start_end(int x, t_game *game)
{
	(void)x;
	if (game->tsc.side == 0)
		game->tsc.perp_wall_dist = (game->tsc.mapx - game->player->pos.x
				+ (1 - game->tsc.stepx) / 2) / game->tsc.ray_dir_x;
	else
		game->tsc.perp_wall_dist = (game->tsc.mapy - game->player->pos.y
				+ (1 - game->tsc.stepy) / 2) / game->tsc.ray_dir_y;
	game->tsc.line_height = (int)(H / 2 / game->tsc.perp_wall_dist);
	game->tsc.draw_start = -game->tsc.line_height / 2 + H / 2;
	if (game->tsc.draw_start < 0)
		game->tsc.draw_start = 0;
	game->tsc.draw_end = game->tsc.line_height / 2 + H / 2;
	if (game->tsc.draw_end >= H)
		game->tsc.draw_end = H - 1;
}
