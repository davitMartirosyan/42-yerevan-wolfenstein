/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 05:46:33 by tumolabs          #+#    #+#             */
/*   Updated: 2023/04/22 06:59:51 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int     rgb(char *txt)
{
    int     i;
    char    *copy;
    char    **split;
    
    copy = ft_strdup(txt);
    i = -1;
    while (copy[++i])
        if (!ft_isdigit(copy[i]))
            copy[i] = 2;
    split = ft_split(copy, 2);
    i = (ft_atoi(split[0]) << 16) | (ft_atoi(split[1]) << 8) | ft_atoi(split[2]);
    free_char_pp(&split);
    free(copy);
    return (i);
}

void	mpp(t_data *data, int x, int y, int color)
{
	char	*dst;
	
	dst = data->addr + (y * data->len + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

void	draw_textured_walls(int x, t_game *game)
{
	int	w;
	
	w = game->tsc.drawStart - 1;
	while (++w < game->tsc.drawEnd)
	{
		//Vertical Wall texturing
		if (game->tsc.side == 0)
		{
			if (game->tsc.rayDirX > 0)
				game->tsc.wallColor = 0xd11f78;
			else
				game->tsc.wallColor = 0x1f63d1;
		}
		//Horizontal Wall texturing
		else
		{
			if (game->tsc.rayDirY > 0)
				game->tsc.wallColor = 0x1fd184;
			else
				game->tsc.wallColor = 0xd1bc1f;
		}
		mpp(&game->img, x, w, game->tsc.wallColor);
	}
}

void	draw_sky(int x, t_game *game)
{
	int	s;
	
	s = -1;
	while (++s < game->tsc.drawStart)
		mpp(&game->img, x, s, game->floor_color);	
}

void	draw_floor(int x, t_game *game)
{
	int	c;
	
	c = game->tsc.drawEnd - 1;
	while (++c < HEIGHT)
		mpp(&game->img, x, c, game->ceiling_color);
}