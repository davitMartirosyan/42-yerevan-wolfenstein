/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 23:58:47 by tumolabs          #+#    #+#             */
/*   Updated: 2023/04/23 05:12:17 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
void	test(t_game *game);

int main(int ac, char **av)
{
    t_game  *game;
    
    if (ac < 2 || ac > 2)
        failure();
    game = init();
    parser(game, av[1]);
	check_dependancies(game);
	// test(game);
    play(game);
}

void	test(t_game *game)
{
	int	w;
	int	h;

	void	*img;
	
	game->screen->mlx = mlx_init();
	game->screen->win = mlx_new_window(game->screen->mlx, 500, 500, "Test");
	mlx_put_image_to_window(game->screen->mlx, game->screen->win, game->dir[0], 10, 10);
	mlx_put_image_to_window(game->screen->mlx, game->screen->win, game->dir[1], 50, 50);
	mlx_put_image_to_window(game->screen->mlx, game->screen->win, game->dir[2], 100, 100);
	mlx_hook(game->screen->win, 2, 1L<<0, update_loop, game);
	mlx_loop(game->screen->mlx);
}

void    play(t_game *game)
{
    game->screen->mlx = mlx_init();
    game->screen->win = mlx_new_window(game->screen->mlx, WIDTH, HEIGHT, "Cub3d");
	game->img.img = mlx_new_image(game->screen->mlx, WIDTH, HEIGHT);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bpp, &game->img.len, &game->img.endian);
	game->player->fov = 2 * atan(0.66 / 1.0);
    draw(game);
	mlx_hook(game->screen->win, 2, 1L<<0, update_loop, game);
	mlx_hook(game->screen->win, 17, 0L, close_win, game);
	mlx_hook(game->screen->win, 6, 0L, mouse_, game);
	mlx_loop(game->screen->mlx);
}

void    draw(t_game *game)
{
	int	s, w, c;	
    int		x;

	x = 0;
	while (x < WIDTH)
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
	mlx_put_image_to_window(game->screen->mlx, game->screen->win, game->img.img, 0, 0);
}

// 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