/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tumolabs <tumolabs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 23:58:24 by tumolabs          #+#    #+#             */
/*   Updated: 2023/04/14 07:14:32 by tumolabs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    parser(t_game *game, char *filename)
{
    game->sdl = create_map_buffer(filename);
    set_instances(game);
    // set_matrix(game);
}

void    set_instances(t_game *game)
{
    int i;

    i = 0;
    while (game->sdl[i])
    {
        if (contains(game->sdl[i], ".xpm"))
        {
            put_textures(game, i);
            game->news++;
        }
        else if (contains(game->sdl[i], ","))
        {
            put_colors(game, i);
            game->colors++;
        }
        else
            game->map = set_map(game->map, '\n', game->sdl[i]);   
        i++;
    }
    if (game->news != 4 || game->colors != 2 || !game->north || !game->south
        || !game->west || !game->east || !game->map)
        failure();
}