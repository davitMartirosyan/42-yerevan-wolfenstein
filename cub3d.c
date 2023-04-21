/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmkhitar <dmkhitar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 23:58:47 by tumolabs          #+#    #+#             */
/*   Updated: 2023/04/22 01:43:37 by dmkhitar         ###   ########.fr       */
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
	printf("%s\n", game->north);
    run(game);
}

void    run(t_game *game)
{
    player(game);
    game->screen->mlx = mlx_init();
    game->screen->win = mlx_new_window(game->screen->mlx, WIDTH, HEIGHT, "Cub3d");
	game->img.img = mlx_new_image(game->screen->mlx, WIDTH, HEIGHT);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bpp, &game->img.len, &game->img.endian);
	play(game);
	mlx_hook(game->screen->win, 2, (1L<<0), update_loop, game);
    mlx_loop(game->screen->mlx);
}

int	update_loop(int keycode, t_game *game)
{
	if (keycode == 13) // W
	{
		game->player->pos.y -= 0.1;
	}
	else if (keycode == 0) // A
	{
		game->player->pos.x -= 0.1;
	}
	else if (keycode == 2) // D
	{
		game->player->pos.x += 0.1;
	}
	else if (keycode == 1) // S
	{
		game->player->pos.y += 0.1;
	}
	draw(game);
	return (1);
}

void    play(t_game *game)
{
    draw(game);
}

void    draw(t_game *game)
{
	// t_texture	texture;
	t_tsc	tsc;
    int		x;
	unsigned	long tw;
	unsigned	long th;


	// texture.texture_p = mlx_xpm_file_to_image(game->screen->mlx, "./textures/xpm/wood.xpm", &texture.width, &texture.height);

	if (set_texture_data(game) == -1)
		exit(1);
	// texture.data = mlx_get_data_addr(texture.texture_p, &texture.bpp, &texture.size_line, &texture.endian);

	// for (texture.y = 0; texture.y < texture.height; texture.y++){
    // 	for (texture.x = 0; texture.x < texture.width; texture.x++){
	// 		// set_rgb(texture);
	// 		// mpp(&game->img, texture.x, texture.y, rgb_tohex(red, green, blue));
	// 		// printf("Pixel at (%d, %d) has color (R:%d, G:%d, B:%d)\n", texture.x, texture.y, texture.red, texture.green, texture.blue);
	// 		// printf("Hex 0x%d\n", rgb_tohex(red, green, blue));
	// 	}
	// }
	// mlx_put_image_to_window(game->screen->mlx, game->screen->win, game->img.img, 0, 0);
	// while (texture.x < texture.width)
	// {
	// 	while (texture.y < texture.height)
	// 	{
	// 		printf("[%s]\n", wood[texture.x][texture.y]);
	// 		texture.y++;
	// 	}
	// 	texture.y = 0;
	// 	texture.x++;
	// }
	x = 0;
	game->texture[0].x = 0;
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
			// mlx_pixel_put(game->screen->mlx, game->screen->win, x, s, game->floor_color);
		w = drawStart - 1;
		//my code
		int	wall_height = drawEnd - w;
		game->texture[0].y = 0;
		if (game->texture[0].x >= game->texture[0].width)
			game->texture[0].x = 0;
		float divide = (float )game->texture[0].height / wall_height;

		while (++w < drawEnd)
		{
			int y = game->texture[0].y * divide;
			unsigned char red;
			unsigned char green;
			unsigned char blue;

			set_rgb(&game->texture[0], &red, &green, &blue, game->texture[0].x, y);

			mpp(&game->img, x, w, rgb_tohex(red, green, blue));
			game->texture[0].y += 1;
		}
		game->texture[0].x++;
			// mlx_pixel_put(game->screen->mlx, game->screen->win, x, w, 0x09a9c9a);
		c = drawEnd - 1;
		// printf("we-%d\n", c);
		while (++c < HEIGHT)
			mpp(&game->img, x, c, game->ceiling_color);
			// mlx_pixel_put(game->screen->mlx, game->screen->win, x, c, game->ceiling_color);
		x++;
    }
	mlx_put_image_to_window(game->screen->mlx, game->screen->win, game->img.img, 0, 0);
}

void	mpp(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->len + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

int get_pixel_hex(t_texture texture, int x, int y)
{
	unsigned char blue = texture.data[x * texture.bpp / 8 + y * texture.size_line];
	unsigned char green = texture.data[x * texture.bpp / 8 + y * texture.size_line + 1];
	unsigned char red = texture.data[x * texture.bpp / 8 + y * texture.size_line + 2];

	return (rgb_tohex(red, green, blue));
}

// void	my_mlx_pixel_put(t_game *game, int x, int y, int clr)
// {
// 	char	*dst;

// 	dst = game->img->addr[1] + ((y * game->img->size_len[1]) + x
// 			* (game->img->bits_per_px[1] / 8));
// 	*(unsigned int *)dst = clr;
// }

// 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
