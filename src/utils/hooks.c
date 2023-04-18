/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 03:47:34 by dmartiro          #+#    #+#             */
/*   Updated: 2023/04/18 03:47:42 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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