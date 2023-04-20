/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 03:47:34 by dmartiro          #+#    #+#             */
/*   Updated: 2023/04/20 05:07:41 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	update_loop(int k, t_game *game)
{
	if (k == 13)
		w(game);
	else if (k == 1)
		s(game);
	else if (k == 0)
		a(game);
	else if (k == 2)
		d(game);
	else if (k == 123 || k == 124)
		left_right(k, game);
	else if (k == 53)
		esc(k, game);
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

int	mouse_(int x, int y, t_game *game)
{
	t_vec	dir;
	t_vec	plane;
	
	if (x )
	if (game->player->mouse_x > x)
	{
		dir = game->player->dir;
		plane = game->player->plane;
		game->player->dir.x = dir.x * cos(ROT * (-1)) - dir.y * sin(ROT * (-1));
		game->player->dir.y = dir.x * sin(ROT * (-1)) + dir.y * cos(ROT * (-1));
		game->player->plane.x = plane.x * cos(ROT * (-1)) - plane.y * sin(ROT * (-1));
		game->player->plane.y = plane.x * sin(ROT * (-1)) + plane.y * cos(ROT * (-1));
	}
	if (game->player->mouse_x < x)
	{
		dir = game->player->dir;
		plane = game->player->plane;
		game->player->dir.x = dir.x * cos(ROT) - dir.y * sin(ROT);
		game->player->dir.y = dir.x * sin(ROT) + dir.y * cos(ROT);
		game->player->plane.x = plane.x * cos(ROT) - plane.y * sin(ROT);
		game->player->plane.y = plane.x * sin(ROT) + plane.y * cos(ROT);
	}
	game->player->mouse_x = x;
	draw(game);
	return (1);
}