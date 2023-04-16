/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tumolabs <tumolabs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 23:58:47 by tumolabs          #+#    #+#             */
/*   Updated: 2023/04/16 01:18:39 by tumolabs         ###   ########.fr       */
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
    run(game);
}

void    run(t_game *game)
{
    player(game);
    game->screen->mlx = mlx_init();
    game->screen->win = mlx_new_window(game->screen->mlx, WIDTH, HEIGHT, "Cub3d");
    // game->img.img = mlx_new_image(game->screen->mlx, WIDTH, HEIGHT);
    // game->img.addr = mlx_get_data_addr(game->img.img,\
    //     &game->img.bpp, &game->img.len, &game->img.endian);
    play(game);
    mlx_loop(game->screen->mlx);
}

void    play(t_game *game)
{
    draw(game);
}

void    draw(t_game *game)
{
    int	x;

	x = 0;

	printf("***********************************\n");
	printf("Pos: {%f} : {%f}\n", game->player->pos.x, game->player->pos.y);
	printf("Dir: {%f} : {%f}\n", game->player->dir.x, game->player->dir.y);
	printf("Plane: {%f} : {%f}\n", game->player->plane.x, game->player->plane.y);
	printf("***********************************\n");

	while (x < WIDTH)
	{
		double cameraX = 2 * x / (double)WIDTH - 1;
		double rayDirX = game->player->dir.x + game->player->plane.x * cameraX;
		double rayDirY = game->player->dir.y + game->player->plane.y * cameraX;
		int mapX = (int)game->player->pos.x;
		int mapY = (int)game->player->pos.y;

		double sideDistX;
		double sideDistY;

		double deltaDistX = fabs(1 / rayDirX);
		double deltaDistY = fabs(1 / rayDirY);

		double perpWallDist;

		int stepX;
		int stepY;

		int hit = 0;
		int side;
		if(rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (game->player->pos.x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - game->player->pos.x) * deltaDistX;
		}
		if(rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (game->player->pos.y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - game->player->pos.y) * deltaDistY;
		}
		while(hit == 0)
		{
			if(sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if(game->mmap && game->mmap[mapY][mapX] == 1)
				hit = 1;
		}
		if(side == 0)
			perpWallDist = (mapX - game->player->pos.x + (1 - stepX) / 2) / rayDirX ;
		else
			perpWallDist = (mapY - game->player->pos.y + (1 - stepY) / 2) / rayDirY ;
			//perpWallDist = (sideDistY - deltaDistY);
		int lineHeight = (int)(HEIGHT / 2 / perpWallDist);
		int drawStart = -lineHeight / 2 + HEIGHT / 2;
		
		if(drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + HEIGHT / 2;
		if(drawEnd >= HEIGHT)
			drawEnd = HEIGHT - 1;
        for(int i = 0; i < drawStart; i++)
			mlx_pixel_put(game->screen->mlx, game->screen->win, x, i, 0xd92032);
        for(int i = drawStart; i < drawEnd; i++)
			mlx_pixel_put(game->screen->mlx, game->screen->win, x, i, 0x0074d7);
        for(int i = drawEnd; i < HEIGHT; i++)
			mlx_pixel_put(game->screen->mlx, game->screen->win, x, i, 0xf9983e);
		x++;
    }
}
// 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