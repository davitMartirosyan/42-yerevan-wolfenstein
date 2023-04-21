/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmkhitar <dmkhitar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 00:26:10 by tumolabs          #+#    #+#             */
/*   Updated: 2023/04/22 01:45:16 by dmkhitar         ###   ########.fr       */
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
    return (game);
}
// my code
int set_texture_data(t_game *game)
{
    int i;

    i = -1;
    game->texture[0].height = 15;
    game->texture[0].texture_p = mlx_xpm_file_to_image(game->screen->mlx, path(game->south), &game->texture[0].width, &game->texture[0].height);
    game->texture[1].texture_p = mlx_xpm_file_to_image(game->screen->mlx, path(game->west), &game->texture[1].width, &game->texture[1].height);
    game->texture[2].texture_p = mlx_xpm_file_to_image(game->screen->mlx, path(game->north), &game->texture[2].width, &game->texture[2].height);
    game->texture[3].texture_p = mlx_xpm_file_to_image(game->screen->mlx, path(game->east), &game->texture[3].width, &game->texture[3].height);
    while (++i <= 3)
    {
        if (game->texture[i].texture_p == NULL)
        {
		    printf("Error loading XPM file.\n");
		    return (-1);
	    }
        game->texture[i].data = mlx_get_data_addr(game->texture[i].texture_p, &game->texture[i].bpp, &game->texture[i].size_line, &game->texture[i].endian);
    }
    return (0);
}
