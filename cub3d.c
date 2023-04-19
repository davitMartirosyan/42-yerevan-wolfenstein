/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 23:58:47 by tumolabs          #+#    #+#             */
/*   Updated: 2023/04/19 23:09:22 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int ac, char **av)
{
    t_game  *game;
    
    if (ac < 2 || ac > 2)
        failure();
    game = init();
    parser(game, av[1]);
    play(game);
}

void    play(t_game *game)
{
    game->screen->mlx = mlx_init();
    game->screen->win = mlx_new_window(game->screen->mlx, WIDTH, HEIGHT, "Cub3d");
	game->img.img = mlx_new_image(game->screen->mlx, WIDTH, HEIGHT);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bpp, &game->img.len, &game->img.endian);
	game->player->fov = 2 * atan(0.66 / 1.0); // -> 66
    draw(game);
	mlx_hook(game->screen->win, 2, 1L<<0, update_loop, game);
	mlx_hook(game->screen->win, 17, 0L, close_win, game);
	mlx_mouse_hook(game->screen->win, mouse_, game);
    mlx_loop(game->screen->mlx);
}

void    draw(t_game *game)
{
	t_tsc	tsc;
    int		x;

	x = 0;
	while (x < WIDTH)
	{
		tsc.cameraX = 2 * x / (double)WIDTH - 1;
		tsc.rayDirX = game->player->dir.x + game->player->plane.x * tsc.cameraX;
		tsc.rayDirY = game->player->dir.y + game->player->plane.y * tsc.cameraX;
		tsc.mapX = (int)game->player->pos.x;
		tsc.mapY = (int)game->player->pos.y;
		tsc.sideDistX = 0;
		tsc.sideDistY = 0;
		tsc.deltaDistX = fabs(1 / tsc.rayDirX);
		tsc.deltaDistY = fabs(1 / tsc.rayDirY);
		tsc.perpWallDist = 0;
		tsc.stepX = 0;
		tsc.stepY = 0;
		tsc.hit = 0;
		tsc.side = 0;
		if(tsc.rayDirX < 0)
		{
			tsc.stepX = -1;
			tsc.sideDistX = (game->player->pos.x - tsc.mapX) * tsc.deltaDistX;
		}
		else
		{
			tsc.stepX = 1;
			tsc.sideDistX = (tsc.mapX + 1.0 - game->player->pos.x) * tsc.deltaDistX;
		}
		if(tsc.rayDirY < 0)
		{
			tsc.stepY = -1;
			tsc.sideDistY = (game->player->pos.y - tsc.mapY) * tsc.deltaDistY;
		}
		else
		{
			tsc.stepY = 1;
			tsc.sideDistY = (tsc.mapY + 1.0 - game->player->pos.y) * tsc.deltaDistY;
		}
		while(tsc.hit == 0)
		{
			if(tsc.sideDistX < tsc.sideDistY)
			{
				tsc.sideDistX += tsc.deltaDistX;
				tsc.mapX += tsc.stepX;
				tsc.side = 0;
			}
			else
			{
				tsc.sideDistY += tsc.deltaDistY;
				tsc.mapY += tsc.stepY;
				tsc.side = 1;
			}
			if(game->mmap && game->mmap[tsc.mapY][tsc.mapX] == 1)
				tsc.hit = 1;
		}
		if(tsc.side == 0)
			tsc.perpWallDist = (tsc.mapX - game->player->pos.x + (1 - tsc.stepX) / 2) / tsc.rayDirX ;
		else
			tsc.perpWallDist = (tsc.mapY - game->player->pos.y + (1 - tsc.stepY) / 2) / tsc.rayDirY ;
		int lineHeight = (int)(HEIGHT / 2 / tsc.perpWallDist);
		int drawStart = -lineHeight / 2 + HEIGHT / 2;
		
		if(drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + HEIGHT / 2;
		if(drawEnd >= HEIGHT)
			drawEnd = HEIGHT - 1;
		int	s, w, c;
		s = -1;
		while (++s < drawStart)
			mpp(&game->img, x, s, game->floor_color);
		w = drawStart - 1;
		while (++w < drawEnd)
			mpp(&game->img, x, w, 0xa17600);
		c = drawEnd - 1;
		while (++c < HEIGHT)
			mpp(&game->img, x, c, game->ceiling_color);
		x++;
    }
	mlx_clear_window(game->screen->mlx, game->screen->win);
	mlx_put_image_to_window(game->screen->mlx, game->screen->win, game->img.img, 0, 0);
}


// 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