/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 23:58:24 by tumolabs          #+#    #+#             */
/*   Updated: 2023/04/24 19:41:04 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parser(t_game *game, char *filename)
{
	game->sdl = create_map_buffer(filename);
	set_instances(game);
	set_matrix(game);
	if (!check_board(game))
		failure();
	if (!player(game))
		failure();
}

void	get_map_sizes(t_game *game, char **split)
{
	while (split[game->map_h])
	{
		if (game->map_w < (int)ft_strlen(split[game->map_h]))
			game->map_w = (int)ft_strlen(split[game->map_h]);
		game->map_h++;
	}
}
