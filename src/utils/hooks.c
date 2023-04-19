/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 03:47:34 by dmartiro          #+#    #+#             */
/*   Updated: 2023/04/19 06:45:58 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	update_loop(int keycode, t_game *game)
{	
	if (keycode == 13) // W
	{
		game->player->pos.y -= 0.1 * sin(game->player->cdir);
	}
	else if (keycode == 0) // A
	{
		game->player->pos.x += 0.1 * cos(game->player->cdir);
	}
	else if (keycode == 2) // D
	{
		game->player->pos.x -= 0.1 * cos(game->player->cdir);
	}
	else if (keycode == 1) // S
	{
		game->player->pos.y += 0.1 * sin(game->player->cdir);
	}
	else if (keycode == 124)
	{
		game->player->old_dir.x = game->player->dir.x;
		game->player->dir.x = game->player->dir.x * cos(0.050) - game->player->dir.y * sin(0.050);
		game->player->dir.y = game->player->old_dir.x * sin(0.050) + game->player->dir.y * cos(0.050);
		game->player->old_plane.x = game->player->plane.x;
		game->player->plane.x = game->player->plane.x * cos(0.050) - game->player->plane.y * sin(0.050);
		game->player->plane.y = game->player->old_plane.x * sin(0.050) + game->player->plane.y * cos(0.050);	
	}
	else if (keycode == 123)
	{
		game->player->old_dir.x = game->player->dir.x;
		game->player->dir.x = game->player->dir.x * cos(-0.050) - game->player->dir.y * sin(-0.050);
		game->player->dir.y = game->player->old_dir.x * sin(-0.050) + game->player->dir.y * cos(-0.050);
		game->player->old_plane.x = game->player->plane.x;
		game->player->plane.x = game->player->plane.x * cos(-0.050) - game->player->plane.y * sin(-0.050);
		game->player->plane.y = game->player->old_plane.x * sin(-0.050) + game->player->plane.y * cos(-0.050);	
	}
	else if (keycode == 53)
		esc(keycode, game);
	draw(game);
	return (1);
}

int	esc(int keycode, t_game *game)
{
	if (keycode == 53)
	{
		mlx_destroy_window(game->screen->mlx, game->screen->win);
		exit(0);
	}
	return (1);
}

int	close_win(t_game *game)
{
	mlx_destroy_window(game->screen->mlx, game->screen->win);
	exit(0);
	return (0);
}
