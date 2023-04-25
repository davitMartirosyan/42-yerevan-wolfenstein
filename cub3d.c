/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmkhitar <dmkhitar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 23:58:47 by tumolabs          #+#    #+#             */
/*   Updated: 2023/04/25 23:23:58 by dmkhitar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_game	*game;

	if (ac < 2 || ac > 2)
		failure();
	game = init();
	parser(game, av[1]);
	check_dependancies(game);
	play(game);
}

void	play(t_game *game)
{
	game->screen->mlx = mlx_init();
	game->screen->win = mlx_new_window(game->screen->mlx, W, H, "Cub3d");
	game->img.img = mlx_new_image(game->screen->mlx, W, H);
	game->img.addr = mlx_get_data_addr(game->img.img,
			&game->img.bpp, &game->img.len, &game->img.endian);
	game->player->fov = 2 * atan(0.66 / 1.0);
	draw(game);
	mlx_hook(game->screen->win, 2, 1L << 0, update_loop, game);
	mlx_hook(game->screen->win, 17, 0L, close_win, game);
	mlx_hook(game->screen->win, 6, 0L, mouse_, game);
	mlx_loop(game->screen->mlx);
}

void	draw(t_game *game)
{
	int	x;

	x = 0;
	while (x < W)
	{
		init_game_tsc(x, game);
		check_rays(game);
		dda_algorithm_loop(game);
		start_end(x, game);
		draw_sky(x, game);
		draw_textured_walls(x, game);
		draw_floor(x, game);
		x++;
	}
	mlx_clear_window(game->screen->mlx, game->screen->win);
	mlx_put_image_to_window(game->screen->mlx,
		game->screen->win, game->img.img, 0, 0);
}
