/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 03:47:34 by dmartiro          #+#    #+#             */
/*   Updated: 2023/04/19 23:15:39 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	update_loop(int k, t_game *game)
{
	if (k == 13)
		w(game);
	else if (k == 1)
		s(game);
	else if (k == 0)
		a(game);
	else if (k == 2)
		d(game);
	else if (k == 123 || k == 124)
		left_right(k, game);
	else if (k == 53)
		esc(k, game);
	draw(game);
	return (1);
}

int	esc(int keycode, t_game *game)
{
	if (keycode == 53)
	{
		mlx_destroy_window(game->screen->mlx, game->screen->win);
		exit(0);
	}
	return (1);
}

int	close_win(t_game *game)
{
	mlx_destroy_window(game->screen->mlx, game->screen->win);
	exit(0);
	return (0);
}

int	mouse_(t_game *game)
{
	return (1);
}