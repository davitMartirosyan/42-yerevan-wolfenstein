/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 00:26:10 by tumolabs          #+#    #+#             */
/*   Updated: 2023/04/18 02:40:42 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_game  *init(void)
{
    t_game  *game;

    game = malloc(sizeof(t_game));
    game->player = malloc(sizeof(t_player));
    game->screen = malloc(sizeof(t_screen));
    if (!game || !game->player)
        failure();
    game->map_h = 0;
    game->map_w = 0;
    game->floor_color = 0;
    game->ceiling_color = 0;
    game->north = 0;
    game->south = 0;
    game->west = 0;
    game->east = 0;
    game->news = 0;
    game->colors = 0;
    game->map = NULL;
	game->player->pdx = 0.0;
	game->player->pdy = 0.0;
	game->player->pa = 0.0;
    return (game);
}