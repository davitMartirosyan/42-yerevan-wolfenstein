/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 05:46:33 by tumolabs          #+#    #+#             */
/*   Updated: 2023/04/24 20:23:12 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_textured_walls(int x, t_game *game)
{
	int			y;
	t_texel		texel;
	t_texture	data;

	checkangle(game, &texel, &data);
	y = game->tsc.drawStart - 1 ;
	texel.wall_x -= floor(texel.wall_x);
	texel.wall_height = game->tsc.drawEnd - y;
	texel.divide = (double)data.h / texel.wall_height;
	data.y = 0;
	while (++y < game->tsc.drawEnd)
	{
		texel.py = data.y * texel.divide;
		texel.px = texel.wall_x * data.w;
		set_rgb(&data, &texel, texel.px, texel.py);
		mpp(&game->img, x, y, rgb_tohex(texel.b, texel.g, texel.r));
		data.y++;
	}
}

void	checkangle(t_game *game, t_texel *texel, t_texture *data)
{
	if (game->tsc.side == 0)
	{
		if (game->tsc.rayDirX > 0)
			*data = game->texture[2];
		else
			*data = game->texture[3];
	}
	else
	{
		if (game->tsc.rayDirY > 0)
			*data = game->texture[0];
		else
			*data = game->texture[1];
	}
	if (game->tsc.side == 0)
		texel->wall_x = game->player->pos.y
			+ game->tsc.perpWallDist * game->tsc.rayDirY;
	else
		texel->wall_x = game->player->pos.x
			+ game->tsc.perpWallDist * game->tsc.rayDirX;
}

void	draw_sky(int x, t_game *game)
{
	int	s;

	s = -1;
	while (++s < game->tsc.drawStart)
		mpp(&game->img, x, s, game->floor_color);
}

void	draw_floor(int x, t_game *game)
{
	int	c;

	c = game->tsc.drawEnd - 1;
	while (++c < H)
		mpp(&game->img, x, c, game->ceiling_color);
}
