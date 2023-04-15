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
    game->img.img = mlx_new_image(game->screen->mlx, WIDTH, HEIGHT);
    game->img.addr = mlx_get_data_addr(game->img.img,\
        &game->img.bpp, &game->img.len, &game->img.endian);
    play(game);
    mlx_loop(game->screen->mlx);
}

void    play(t_game *game)
{
    
}

// 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