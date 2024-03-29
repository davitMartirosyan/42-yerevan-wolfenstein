/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 22:58:16 by dmartiro          #+#    #+#             */
/*   Updated: 2023/04/24 20:17:14 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	w(t_game *game)
{
	game->player->pos.x += game->player->dir.x * SPEED;
	game->player->pos.y += game->player->dir.y * SPEED;
}

void	s(t_game *game)
{
	game->player->pos.x -= game->player->dir.x * SPEED;
	game->player->pos.y -= game->player->dir.y * SPEED;
}

void	a(t_game *game)
{
	t_vec	move_vector;

	move_vector.x = -game->player->dir.y;
	move_vector.y = game->player->dir.x;
	game->player->pos.x -= move_vector.x * SPEED;
	game->player->pos.y -= move_vector.y * SPEED;
}

void	d(t_game *game)
{
	t_vec	move_vector;

	move_vector.x = -game->player->dir.y;
	move_vector.y = game->player->dir.x;
	game->player->pos.x += move_vector.x * SPEED;
	game->player->pos.y += move_vector.y * SPEED;
}

void	left_right(int k, t_game *game)
{
	t_vec	dir;
	t_vec	pl;

	if (k == 123)
	{
		dir = game->player->dir;
		pl = game->player->plane;
		game->player->dir.x = dir.x * cos(ROT * (-1)) - dir.y * sin(ROT * (-1));
		game->player->dir.y = dir.x * sin(ROT * (-1)) + dir.y * cos(ROT * (-1));
		game->player->plane.x = pl.x * cos(ROT * (-1)) - pl.y * sin(ROT * (-1));
		game->player->plane.y = pl.x * sin(ROT * (-1)) + pl.y * cos(ROT * (-1));
	}
	else if (k == 124)
	{
		dir = game->player->dir;
		pl = game->player->plane;
		game->player->dir.x = dir.x * cos(ROT) - dir.y * sin(ROT);
		game->player->dir.y = dir.x * sin(ROT) + dir.y * cos(ROT);
		game->player->plane.x = pl.x * cos(ROT) - pl.y * sin(ROT);
		game->player->plane.y = pl.x * sin(ROT) + pl.y * cos(ROT);
	}
}
